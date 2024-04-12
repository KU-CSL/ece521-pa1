#include "ECE521intrin.h"
#include "logger.h"

//******************
//* Implementation *
//******************

__ece521_mask _ece521_init_ones(int first) {
  __ece521_mask mask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    mask.value[i] = (i<first) ? true : false;
  }
  return mask;
}

__ece521_mask _ece521_mask_not(__ece521_mask &maska) {
  __ece521_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = !maska.value[i];
  }
  ECE521Logger.addLog("masknot", _ece521_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__ece521_mask _ece521_mask_or(__ece521_mask &maska, __ece521_mask &maskb) {
  __ece521_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] | maskb.value[i];
  }
  ECE521Logger.addLog("maskor", _ece521_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

__ece521_mask _ece521_mask_and(__ece521_mask &maska, __ece521_mask &maskb) {
  __ece521_mask resultMask;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    resultMask.value[i] = maska.value[i] && maskb.value[i];
  }
  ECE521Logger.addLog("maskand", _ece521_init_ones(), VECTOR_WIDTH);
  return resultMask;
}

int _ece521_cntbits(__ece521_mask &maska) {
  int count = 0;
  for (int i=0; i<VECTOR_WIDTH; i++) {
    if (maska.value[i]) count++;
  }
  ECE521Logger.addLog("cntbits", _ece521_init_ones(), VECTOR_WIDTH);
  return count;
}

template <typename T>
void _ece521_vset(__ece521_vec<T> &vecResult, T value, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? value : vecResult.value[i];
  }
  ECE521Logger.addLog("vset", mask, VECTOR_WIDTH);
}

template void _ece521_vset<float>(__ece521_vec_float &vecResult, float value, __ece521_mask &mask);
template void _ece521_vset<int>(__ece521_vec_int &vecResult, int value, __ece521_mask &mask);

void _ece521_vset_float(__ece521_vec_float &vecResult, float value, __ece521_mask &mask) { _ece521_vset<float>(vecResult, value, mask); }
void _ece521_vset_int(__ece521_vec_int &vecResult, int value, __ece521_mask &mask) { _ece521_vset<int>(vecResult, value, mask); }

__ece521_vec_float _ece521_vset_float(float value) {
  __ece521_vec_float vecResult;
  __ece521_mask mask = _ece521_init_ones();
  _ece521_vset_float(vecResult, value, mask);
  return vecResult;
}
__ece521_vec_int _ece521_vset_int(int value) {
  __ece521_vec_int vecResult;
  __ece521_mask mask = _ece521_init_ones();
  _ece521_vset_int(vecResult, value, mask);
  return vecResult;
}

template <typename T>
void _ece521_vmove(__ece521_vec<T> &dest, __ece521_vec<T> &src, __ece521_mask &mask) {
    for (int i = 0; i < VECTOR_WIDTH; i++) {
        dest.value[i] = mask.value[i] ? src.value[i] : dest.value[i];
    }
    ECE521Logger.addLog("vmove", mask, VECTOR_WIDTH);
}

template void _ece521_vmove<float>(__ece521_vec_float &dest, __ece521_vec_float &src, __ece521_mask &mask);
template void _ece521_vmove<int>(__ece521_vec_int &dest, __ece521_vec_int &src, __ece521_mask &mask);

void _ece521_vmove_float(__ece521_vec_float &dest, __ece521_vec_float &src, __ece521_mask &mask) { _ece521_vmove<float>(dest, src, mask); }
void _ece521_vmove_int(__ece521_vec_int &dest, __ece521_vec_int &src, __ece521_mask &mask) { _ece521_vmove<int>(dest, src, mask); }

template <typename T>
void _ece521_vload(__ece521_vec<T> &dest, T* src, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest.value[i] = mask.value[i] ? src[i] : dest.value[i];
  }
  ECE521Logger.addLog("vload", mask, VECTOR_WIDTH);
}

template void _ece521_vload<float>(__ece521_vec_float &dest, float* src, __ece521_mask &mask);
template void _ece521_vload<int>(__ece521_vec_int &dest, int* src, __ece521_mask &mask);

void _ece521_vload_float(__ece521_vec_float &dest, float* src, __ece521_mask &mask) { _ece521_vload<float>(dest, src, mask); }
void _ece521_vload_int(__ece521_vec_int &dest, int* src, __ece521_mask &mask) { _ece521_vload<int>(dest, src, mask); }

template <typename T>
void _ece521_vstore(T* dest, __ece521_vec<T> &src, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    dest[i] = mask.value[i] ? src.value[i] : dest[i];
  }
  ECE521Logger.addLog("vstore", mask, VECTOR_WIDTH);
}

template void _ece521_vstore<float>(float* dest, __ece521_vec_float &src, __ece521_mask &mask);
template void _ece521_vstore<int>(int* dest, __ece521_vec_int &src, __ece521_mask &mask);

void _ece521_vstore_float(float* dest, __ece521_vec_float &src, __ece521_mask &mask) { _ece521_vstore<float>(dest, src, mask); }
void _ece521_vstore_int(int* dest, __ece521_vec_int &src, __ece521_mask &mask) { _ece521_vstore<int>(dest, src, mask); }

template <typename T>
void _ece521_vadd(__ece521_vec<T> &vecResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] + vecb.value[i]) : vecResult.value[i];
  }
  ECE521Logger.addLog("vadd", mask, VECTOR_WIDTH);
}

template void _ece521_vadd<float>(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vadd<int>(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vadd_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vadd<float>(vecResult, veca, vecb, mask); }
void _ece521_vadd_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vadd<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _ece521_vsub(__ece521_vec<T> &vecResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] - vecb.value[i]) : vecResult.value[i];
  }
  ECE521Logger.addLog("vsub", mask, VECTOR_WIDTH);
}

template void _ece521_vsub<float>(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vsub<int>(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vsub_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vsub<float>(vecResult, veca, vecb, mask); }
void _ece521_vsub_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vsub<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _ece521_vmult(__ece521_vec<T> &vecResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] * vecb.value[i]) : vecResult.value[i];
  }
  ECE521Logger.addLog("vmult", mask, VECTOR_WIDTH);
}

template void _ece521_vmult<float>(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vmult<int>(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vmult_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vmult<float>(vecResult, veca, vecb, mask); }
void _ece521_vmult_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vmult<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _ece521_vdiv(__ece521_vec<T> &vecResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (veca.value[i] / vecb.value[i]) : vecResult.value[i];
  }
  ECE521Logger.addLog("vdiv", mask, VECTOR_WIDTH);
}

template void _ece521_vdiv<float>(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vdiv<int>(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vdiv_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vdiv<float>(vecResult, veca, vecb, mask); }
void _ece521_vdiv_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vdiv<int>(vecResult, veca, vecb, mask); }

template <typename T>
void _ece521_vabs(__ece521_vec<T> &vecResult, __ece521_vec<T> &veca, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    vecResult.value[i] = mask.value[i] ? (abs(veca.value[i])) : vecResult.value[i];
  }
  ECE521Logger.addLog("vabs", mask, VECTOR_WIDTH);
}

template void _ece521_vabs<float>(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_mask &mask);
template void _ece521_vabs<int>(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_mask &mask);

void _ece521_vabs_float(__ece521_vec_float &vecResult, __ece521_vec_float &veca, __ece521_mask &mask) { _ece521_vabs<float>(vecResult, veca, mask); }
void _ece521_vabs_int(__ece521_vec_int &vecResult, __ece521_vec_int &veca, __ece521_mask &mask) { _ece521_vabs<int>(vecResult, veca, mask); }

template <typename T>
void _ece521_vgt(__ece521_mask &maskResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] > vecb.value[i]) : maskResult.value[i];
  }
  ECE521Logger.addLog("vgt", mask, VECTOR_WIDTH);
}

template void _ece521_vgt<float>(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vgt<int>(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vgt_float(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vgt<float>(maskResult, veca, vecb, mask); }
void _ece521_vgt_int(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vgt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _ece521_vlt(__ece521_mask &maskResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] < vecb.value[i]) : maskResult.value[i];
  }
  ECE521Logger.addLog("vlt", mask, VECTOR_WIDTH);
}

template void _ece521_vlt<float>(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_vlt<int>(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_vlt_float(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_vlt<float>(maskResult, veca, vecb, mask); }
void _ece521_vlt_int(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_vlt<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _ece521_veq(__ece521_mask &maskResult, __ece521_vec<T> &veca, __ece521_vec<T> &vecb, __ece521_mask &mask) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    maskResult.value[i] = mask.value[i] ? (veca.value[i] == vecb.value[i]) : maskResult.value[i];
  }
  ECE521Logger.addLog("veq", mask, VECTOR_WIDTH);
}

template void _ece521_veq<float>(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask);
template void _ece521_veq<int>(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask);

void _ece521_veq_float(__ece521_mask &maskResult, __ece521_vec_float &veca, __ece521_vec_float &vecb, __ece521_mask &mask) { _ece521_veq<float>(maskResult, veca, vecb, mask); }
void _ece521_veq_int(__ece521_mask &maskResult, __ece521_vec_int &veca, __ece521_vec_int &vecb, __ece521_mask &mask) { _ece521_veq<int>(maskResult, veca, vecb, mask); }

template <typename T>
void _ece521_hadd(__ece521_vec<T> &vecResult, __ece521_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH/2; i++) {
    T result = vec.value[2*i] + vec.value[2*i+1];
    vecResult.value[2 * i] = result;
    vecResult.value[2 * i + 1] = result;
  }
}

template void _ece521_hadd<float>(__ece521_vec_float &vecResult, __ece521_vec_float &vec);

void _ece521_hadd_float(__ece521_vec_float &vecResult, __ece521_vec_float &vec) { _ece521_hadd<float>(vecResult, vec); }

template <typename T>
void _ece521_interleave(__ece521_vec<T> &vecResult, __ece521_vec<T> &vec) {
  for (int i=0; i<VECTOR_WIDTH; i++) {
    int index = i < VECTOR_WIDTH/2 ? (2 * i) : (2 * (i - VECTOR_WIDTH/2) + 1);
    vecResult.value[i] = vec.value[index];
  }
}

template void _ece521_interleave<float>(__ece521_vec_float &vecResult, __ece521_vec_float &vec);

void _ece521_interleave_float(__ece521_vec_float &vecResult, __ece521_vec_float &vec) { _ece521_interleave<float>(vecResult, vec); }

void addUserLog(const char * logStr) {
  ECE521Logger.addLog(logStr, _ece521_init_ones(), 0);
}

