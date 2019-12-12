/*
 * projeto.c
 *
 * Code generation for model "projeto".
 *
 * Model version              : 1.28
 * Simulink Coder version : 8.8 (R2015a) 09-Feb-2015
 * C source code generated on : Thu Dec 12 16:06:38 2019
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "projeto.h"
#include "projeto_private.h"

/* Block signals (auto storage) */
B_projeto_T projeto_B;

/* Block states (auto storage) */
DW_projeto_T projeto_DW;

/* Real-time model */
RT_MODEL_projeto_T projeto_M_;
RT_MODEL_projeto_T *const projeto_M = &projeto_M_;
static void rate_scheduler(void);

/*
 *   This function updates active task flag for each subrate.
 * The function is called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (projeto_M->Timing.TaskCounters.TID[1])++;
  if ((projeto_M->Timing.TaskCounters.TID[1]) > 1023) {/* Sample time: [0.023219954648526078s, 0.0s] */
    projeto_M->Timing.TaskCounters.TID[1] = 0;
  }

  (projeto_M->Timing.TaskCounters.TID[2])++;
  if ((projeto_M->Timing.TaskCounters.TID[2]) > 10239) {/* Sample time: [0.23219954648526078s, 0.0s] */
    projeto_M->Timing.TaskCounters.TID[2] = 0;
  }
}

void RandSrcInitState_U_64(const uint32_T seed[], real_T state[], int32_T nChans)
{
  int32_T i;
  uint32_T j;
  int32_T k;
  int32_T n;
  real_T d;

  /* InitializeConditions for S-Function (sdsprandsrc2): '<S45>/Random Source' */
  /* RandSrcInitState_U_64 */
  for (i = 0; i < nChans; i++) {
    j = seed[i] != 0U ? seed[i] : 2147483648U;
    state[35 * i + 34] = j;
    for (k = 0; k < 32; k++) {
      d = 0.0;
      for (n = 0; n < 53; n++) {
        j ^= j << 13;
        j ^= j >> 17;
        j ^= j << 5;
        d = (real_T)((int32_T)(j >> 19) & 1) + (d + d);
      }

      state[35 * i + k] = ldexp(d, -53);
    }

    state[35 * i + 32] = 0.0;
    state[35 * i + 33] = 0.0;
  }

  /* End of InitializeConditions for S-Function (sdsprandsrc2): '<S45>/Random Source' */
}

void RandSrc_U_D(real_T y[], const real_T minVec[], int32_T minLen, const real_T
                 maxVec[], int32_T maxLen, real_T state[], int32_T nChans,
                 int32_T nSamps)
{
  int32_T one;
  int32_T lsw;
  int8_T *onePtr;
  int32_T chan;
  real_T min;
  real_T max;
  int32_T samps;
  real_T d;
  int32_T i;
  uint32_T j;

  /* S-Function (sdsprandsrc2): '<S45>/Random Source' */
  /* RandSrc_U_D */
  one = 1;
  onePtr = (int8_T *)&one;
  lsw = (onePtr[0U] == 0);
  for (chan = 0; chan < nChans; chan++) {
    min = minVec[minLen > 1 ? chan : 0];
    max = maxVec[maxLen > 1 ? chan : 0];
    max -= min;
    i = (int32_T)((uint32_T)state[chan * 35 + 33] & 31U);
    j = (uint32_T)state[chan * 35 + 34];
    for (samps = 0; samps < nSamps; samps++) {
      /* "Subtract with borrow" generator */
      d = state[((i + 20) & 31) + chan * 35];
      d -= state[((i + 5) & 31) + chan * 35];
      d -= state[chan * 35 + 32];
      if (d >= 0.0) {
        state[chan * 35 + 32] = 0.0;
      } else {
        d++;

        /* set 1 in LSB */
        state[chan * 35 + 32] = 1.1102230246251565E-16;
      }

      state[chan * 35 + i] = d;
      i = (i + 1) & 31;

      /* XOR with shift register sequence */
      ((int32_T *)&d)[lsw] ^= j;
      j ^= j << 13;
      j ^= j >> 17;
      j ^= j << 5;
      ((int32_T *)&d)[lsw ^ 1] ^= j & 1048575U;
      y[chan * nSamps + samps] = max * d + min;
    }

    state[chan * 35 + 33] = i;
    state[chan * 35 + 34] = j;
  }

  /* End of S-Function (sdsprandsrc2): '<S45>/Random Source' */
}

/* Model step function */
void projeto_step(void)
{
  /* local block i/o variables */
  real_T rtb_RateTransition;
  real_T rtb_dig_out;
  real_T rtb_digito;
  boolean_T rtb_yl1[1024];
  char_T *sErr;
  void *audio;
  int32_T uyIdx;
  int32_T currentOffset;
  int32_T nSamps;
  int32_T k;
  real_T numAccum;
  int32_T i;
  real_T rtb_count_out;
  boolean_T tmp;
  if (projeto_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
    sErr = GetErrorBuffer(&projeto_DW.FromMultimediaFile_HostLib[0U]);
    audio = (void *)&projeto_B.FromMultimediaFile[0U];
    LibOutputs_FromMMFile(&projeto_DW.FromMultimediaFile_HostLib[0U],
                          GetNullPointer(), audio, GetNullPointer(),
                          GetNullPointer(), GetNullPointer());
    if (*sErr != 0) {
      rtmSetErrorStatus(projeto_M, sErr);
      rtmSetStopRequested(projeto_M, 1);
    }

    /* End of S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
  }

  /* S-Function (sdsprandsrc2): '<S45>/Random Source' */
  RandSrc_U_D(&projeto_B.RandomSource, &projeto_P.UniformNoiseGenerator_low, 1,
              &projeto_P.UniformNoiseGenerator_up, 1,
              projeto_DW.RandomSource_STATE_DWORK, 1, 1);

  /* Buffer: '<S3>/Buffer' */
  nSamps = 1;
  k = 2048 - projeto_DW.Buffer_inBufPtrIdx;
  uyIdx = projeto_DW.Buffer_inBufPtrIdx;
  if (k <= 1) {
    i = 0;
    while (i < k) {
      projeto_DW.Buffer_CircBuf[projeto_DW.Buffer_inBufPtrIdx] =
        projeto_B.RandomSource;
      i = 1;
    }

    uyIdx = 0;
    nSamps = 1 - k;
  }

  for (i = 0; i < nSamps; i++) {
    projeto_DW.Buffer_CircBuf[uyIdx + i] = projeto_B.RandomSource;
  }

  projeto_DW.Buffer_inBufPtrIdx++;
  if (projeto_DW.Buffer_inBufPtrIdx >= 2048) {
    projeto_DW.Buffer_inBufPtrIdx -= 2048;
  }

  projeto_DW.Buffer_bufferLength++;
  if (projeto_DW.Buffer_bufferLength > 2048) {
    projeto_DW.Buffer_outBufPtrIdx = (projeto_DW.Buffer_outBufPtrIdx +
      projeto_DW.Buffer_bufferLength) - 2048;
    if (projeto_DW.Buffer_outBufPtrIdx > 2048) {
      projeto_DW.Buffer_outBufPtrIdx -= 2048;
    }

    projeto_DW.Buffer_bufferLength = 2048;
  }

  if (projeto_M->Timing.TaskCounters.TID[1] == 0) {
    projeto_DW.Buffer_bufferLength -= 1024;
    if (projeto_DW.Buffer_bufferLength < 0) {
      projeto_DW.Buffer_outBufPtrIdx += projeto_DW.Buffer_bufferLength;
      if (projeto_DW.Buffer_outBufPtrIdx < 0) {
        projeto_DW.Buffer_outBufPtrIdx += 2048;
      }

      projeto_DW.Buffer_bufferLength = 0;
    }

    uyIdx = 0;
    currentOffset = projeto_DW.Buffer_outBufPtrIdx;
    if (projeto_DW.Buffer_outBufPtrIdx < 0) {
      currentOffset = projeto_DW.Buffer_outBufPtrIdx + 2048;
    }

    k = 2048 - currentOffset;
    nSamps = 1024;
    if (k <= 1024) {
      for (i = 0; i < k; i++) {
        projeto_B.Sum1[i] = projeto_DW.Buffer_CircBuf[currentOffset + i];
      }

      uyIdx = k;
      currentOffset = 0;
      nSamps = 1024 - k;
    }

    for (i = 0; i < nSamps; i++) {
      projeto_B.Sum1[uyIdx + i] = projeto_DW.Buffer_CircBuf[currentOffset + i];
    }

    projeto_DW.Buffer_outBufPtrIdx = currentOffset + nSamps;

    /* ManualSwitch: '<S3>/Insere ru?do' */
    tmp = (projeto_P.Insererudo_CurrentSetting == 1);
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      rtb_count_out = projeto_B.Sum1[nSamps];
      if (!tmp) {
        rtb_count_out = 0.0;
      }

      projeto_B.Sum1[nSamps] = rtb_count_out;
    }

    /* End of ManualSwitch: '<S3>/Insere ru?do' */

    /* Sum: '<S3>/Sum' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      rtb_count_out = projeto_B.FromMultimediaFile[nSamps] +
        projeto_B.Sum1[nSamps];
      projeto_B.Sum1[nSamps] = rtb_count_out;
    }

    /* End of Sum: '<S3>/Sum' */

    /* S-Function (sdspbiquad): '<S46>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.023793155902006719 * projeto_B.Sum1[uyIdx] -
                       -1.8671135085561661 *
                       projeto_DW.DigitalFilter_FILT_STATES[0]) -
        0.9622861321641929 * projeto_DW.DigitalFilter_FILT_STATES[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES[0] + rtb_count_out)
        + projeto_DW.DigitalFilter_FILT_STATES[1];
      projeto_DW.DigitalFilter_FILT_STATES[1] =
        projeto_DW.DigitalFilter_FILT_STATES[0];
      projeto_DW.DigitalFilter_FILT_STATES[0] = rtb_count_out;
      rtb_count_out = (0.013102355929817504 * numAccum - -1.8467982180239273 *
                       projeto_DW.DigitalFilter_FILT_STATES[2]) -
        0.89920764174319756 * projeto_DW.DigitalFilter_FILT_STATES[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES[2] + rtb_count_out)
        + projeto_DW.DigitalFilter_FILT_STATES[3];
      projeto_DW.DigitalFilter_FILT_STATES[3] =
        projeto_DW.DigitalFilter_FILT_STATES[2];
      projeto_DW.DigitalFilter_FILT_STATES[2] = rtb_count_out;
      rtb_count_out = (0.0029056649844451336 * numAccum - -1.8518222248474006 *
                       projeto_DW.DigitalFilter_FILT_STATES[4]) -
        0.86344488478518122 * projeto_DW.DigitalFilter_FILT_STATES[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES[4] + rtb_count_out)
        + projeto_DW.DigitalFilter_FILT_STATES[5];
      projeto_DW.DigitalFilter_FILT_STATES[5] =
        projeto_DW.DigitalFilter_FILT_STATES[4];
      projeto_DW.DigitalFilter_FILT_STATES[4] = rtb_count_out;
      projeto_B.DigitalFilter[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S46>/Digital Filter' */

    /* DownSample: '<S4>/Downsample' */
    if (projeto_M->Timing.TaskCounters.TID[2] == 0) {
      memcpy(&projeto_B.Downsample[0], &projeto_DW.Downsample_Buffer[0], sizeof
             (real_T) << 10U);
      projeto_DW.Downsample_InBufIdx = 0;
    }

    if (projeto_DW.Downsample_InBufIdx >= 1024) {
      projeto_DW.Downsample_InBufIdx = 0;
    }

    nSamps = projeto_DW.Downsample_InBufIdx;
    k = projeto_DW.Downsample_Count;
    for (i = 0; i < 1024; i++) {
      if (k == 0) {
        projeto_DW.Downsample_Buffer[nSamps] = projeto_B.DigitalFilter[i];
        nSamps++;
      }

      k++;
      if (k == 10) {
        k = 0;
      }
    }

    projeto_DW.Downsample_InBufIdx = nSamps;
    projeto_DW.Downsample_Count = k;

    /* End of DownSample: '<S4>/Downsample' */
  }

  /* End of Buffer: '<S3>/Buffer' */
  if (projeto_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (sdspbiquad): '<S19>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.41312040835564962 * projeto_B.Downsample[uyIdx] -
                       -0.10151712589667007 *
                       projeto_DW.DigitalFilter_FILT_STATES_o[0]) -
        0.75399875931926841 * projeto_DW.DigitalFilter_FILT_STATES_o[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_o[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_o[1];
      projeto_DW.DigitalFilter_FILT_STATES_o[1] =
        projeto_DW.DigitalFilter_FILT_STATES_o[0];
      projeto_DW.DigitalFilter_FILT_STATES_o[0] = rtb_count_out;
      rtb_count_out = (0.13328738916997307 * numAccum - -0.79029843035405123 *
                       projeto_DW.DigitalFilter_FILT_STATES_o[2]) -
        0.32344798703394356 * projeto_DW.DigitalFilter_FILT_STATES_o[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_o[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_o[3];
      projeto_DW.DigitalFilter_FILT_STATES_o[3] =
        projeto_DW.DigitalFilter_FILT_STATES_o[2];
      projeto_DW.DigitalFilter_FILT_STATES_o[2] = rtb_count_out;
      projeto_B.DigitalFilter_o[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S19>/Digital Filter' */

    /* DiscreteFir: '<S24>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 104; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients[nSamps];
      }

      for (nSamps = 0; nSamps < 104 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients[(i + nSamps) + 1] *
          projeto_DW.DigitalFilter_states[nSamps];
      }

      projeto_B.DigitalFilter_k[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 104; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 105; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients[nSamps];
      }

      projeto_B.DigitalFilter_k[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 104; i++) {
      projeto_DW.DigitalFilter_states[103 - i] = projeto_B.DigitalFilter_o[i +
        920];
    }

    /* End of DiscreteFir: '<S24>/Digital Filter' */

    /* Delay: '<S2>/Delay' */
    memcpy(&projeto_B.Abs3[0], &projeto_DW.Delay_DSTATE[0], 12U * sizeof(real_T));
    memcpy(&projeto_B.Abs3[12], &projeto_B.DigitalFilter_k[0], 1012U * sizeof
           (real_T));

    /* Abs: '<S2>/Abs6' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs6' */

    /* S-Function (sdspbiquad): '<S15>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050790700054787071 * projeto_B.Abs3[uyIdx] -
                       -1.9923461255118937 *
                       projeto_DW.DigitalFilter_FILT_STATES_i[0]) -
        0.99437775351408519 * projeto_DW.DigitalFilter_FILT_STATES_i[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_i[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_i[1];
      projeto_DW.DigitalFilter_FILT_STATES_i[1] =
        projeto_DW.DigitalFilter_FILT_STATES_i[0];
      projeto_DW.DigitalFilter_FILT_STATES_i[0] = rtb_count_out;
      rtb_count_out = (0.00028459697566485996 * numAccum - -1.9835723983392863 *
                       projeto_DW.DigitalFilter_FILT_STATES_i[2]) -
        0.98471078624194563 * projeto_DW.DigitalFilter_FILT_STATES_i[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_i[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_i[3];
      projeto_DW.DigitalFilter_FILT_STATES_i[3] =
        projeto_DW.DigitalFilter_FILT_STATES_i[2];
      projeto_DW.DigitalFilter_FILT_STATES_i[2] = rtb_count_out;
      rtb_count_out = (6.3472708451233148E-5 * numAccum - -1.9789143415593364 *
                       projeto_DW.DigitalFilter_FILT_STATES_i[4]) -
        0.97916823239314155 * projeto_DW.DigitalFilter_FILT_STATES_i[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_i[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_i[5];
      projeto_DW.DigitalFilter_FILT_STATES_i[5] =
        projeto_DW.DigitalFilter_FILT_STATES_i[4];
      projeto_DW.DigitalFilter_FILT_STATES_i[4] = rtb_count_out;
      projeto_B.DigitalFilter_h[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S15>/Digital Filter' */

    /* DiscreteFir: '<S25>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 127; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_a[nSamps];
      }

      for (nSamps = 0; nSamps < 127 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_a[(i + nSamps) + 1]
          * projeto_DW.DigitalFilter_states_k[nSamps];
      }

      projeto_B.Abs3[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 127; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 128; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_a[nSamps];
      }

      projeto_B.Abs3[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 127; i++) {
      projeto_DW.DigitalFilter_states_k[126 - i] = projeto_B.DigitalFilter_o[i +
        897];
    }

    /* End of DiscreteFir: '<S25>/Digital Filter' */

    /* Abs: '<S2>/Abs4' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs4' */

    /* S-Function (sdspbiquad): '<S16>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_p[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_p[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_p[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_p[1];
      projeto_DW.DigitalFilter_FILT_STATES_p[1] =
        projeto_DW.DigitalFilter_FILT_STATES_p[0];
      projeto_DW.DigitalFilter_FILT_STATES_p[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_p[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_p[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_p[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_p[3];
      projeto_DW.DigitalFilter_FILT_STATES_p[3] =
        projeto_DW.DigitalFilter_FILT_STATES_p[2];
      projeto_DW.DigitalFilter_FILT_STATES_p[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_p[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_p[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_p[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_p[5];
      projeto_DW.DigitalFilter_FILT_STATES_p[5] =
        projeto_DW.DigitalFilter_FILT_STATES_p[4];
      projeto_DW.DigitalFilter_FILT_STATES_p[4] = rtb_count_out;
      projeto_B.DigitalFilter_hk[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S16>/Digital Filter' */

    /* DiscreteFir: '<S9>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 127; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_c[nSamps];
      }

      for (nSamps = 0; nSamps < 127 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_c[(i + nSamps) + 1]
          * projeto_DW.DigitalFilter_states_m[nSamps];
      }

      projeto_B.Abs3[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 127; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 128; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_c[nSamps];
      }

      projeto_B.Abs3[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 127; i++) {
      projeto_DW.DigitalFilter_states_m[126 - i] = projeto_B.DigitalFilter_o[i +
        897];
    }

    /* End of DiscreteFir: '<S9>/Digital Filter' */

    /* Abs: '<S2>/Abs5' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs5' */

    /* S-Function (sdspbiquad): '<S14>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_m[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_m[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m[1];
      projeto_DW.DigitalFilter_FILT_STATES_m[1] =
        projeto_DW.DigitalFilter_FILT_STATES_m[0];
      projeto_DW.DigitalFilter_FILT_STATES_m[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_m[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_m[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m[3];
      projeto_DW.DigitalFilter_FILT_STATES_m[3] =
        projeto_DW.DigitalFilter_FILT_STATES_m[2];
      projeto_DW.DigitalFilter_FILT_STATES_m[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_m[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_m[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m[5];
      projeto_DW.DigitalFilter_FILT_STATES_m[5] =
        projeto_DW.DigitalFilter_FILT_STATES_m[4];
      projeto_DW.DigitalFilter_FILT_STATES_m[4] = rtb_count_out;
      projeto_B.DigitalFilter_e[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S14>/Digital Filter' */

    /* DiscreteFir: '<S26>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 117; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_g[nSamps];
      }

      for (nSamps = 0; nSamps < 117 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_g[(i + nSamps) + 1]
          * projeto_DW.DigitalFilter_states_a[nSamps];
      }

      projeto_B.DigitalFilter_h_m[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 117; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 118; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_g[nSamps];
      }

      projeto_B.DigitalFilter_h_m[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 117; i++) {
      projeto_DW.DigitalFilter_states_a[116 - i] = projeto_B.DigitalFilter_o[i +
        907];
    }

    /* End of DiscreteFir: '<S26>/Digital Filter' */

    /* Delay: '<S2>/Delay1' */
    for (nSamps = 0; nSamps < 5; nSamps++) {
      projeto_B.Abs3[nSamps] = projeto_DW.Delay1_DSTATE[nSamps];
    }

    memcpy(&projeto_B.Abs3[5], &projeto_B.DigitalFilter_h_m[0], 1019U * sizeof
           (real_T));

    /* End of Delay: '<S2>/Delay1' */

    /* Abs: '<S2>/Abs7' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs7' */

    /* S-Function (sdspbiquad): '<S17>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_m4[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_m4[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m4[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m4[1];
      projeto_DW.DigitalFilter_FILT_STATES_m4[1] =
        projeto_DW.DigitalFilter_FILT_STATES_m4[0];
      projeto_DW.DigitalFilter_FILT_STATES_m4[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_m4[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_m4[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m4[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m4[3];
      projeto_DW.DigitalFilter_FILT_STATES_m4[3] =
        projeto_DW.DigitalFilter_FILT_STATES_m4[2];
      projeto_DW.DigitalFilter_FILT_STATES_m4[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_m4[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_m4[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_m4[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_m4[5];
      projeto_DW.DigitalFilter_FILT_STATES_m4[5] =
        projeto_DW.DigitalFilter_FILT_STATES_m4[4];
      projeto_DW.DigitalFilter_FILT_STATES_m4[4] = rtb_count_out;
      projeto_B.DigitalFilter_n[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S17>/Digital Filter' */

    /* S-Function (sdspbiquad): '<S18>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.45789760142368552 * projeto_B.Downsample[uyIdx] -
                       -0.077741485206355168 *
                       projeto_DW.DigitalFilter_FILT_STATES_d[0]) -
        0.75384892048838681 * projeto_DW.DigitalFilter_FILT_STATES_d[1];
      numAccum = (-2.0 * projeto_DW.DigitalFilter_FILT_STATES_d[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_d[1];
      projeto_DW.DigitalFilter_FILT_STATES_d[1] =
        projeto_DW.DigitalFilter_FILT_STATES_d[0];
      projeto_DW.DigitalFilter_FILT_STATES_d[0] = rtb_count_out;
      rtb_count_out = (0.15332135120394927 * numAccum - 0.68414800094922334 *
                       projeto_DW.DigitalFilter_FILT_STATES_d[2]) -
        0.29743340576502053 * projeto_DW.DigitalFilter_FILT_STATES_d[3];
      numAccum = (-2.0 * projeto_DW.DigitalFilter_FILT_STATES_d[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_d[3];
      projeto_DW.DigitalFilter_FILT_STATES_d[3] =
        projeto_DW.DigitalFilter_FILT_STATES_d[2];
      projeto_DW.DigitalFilter_FILT_STATES_d[2] = rtb_count_out;
      projeto_B.DigitalFilter_o[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S18>/Digital Filter' */

    /* DiscreteFir: '<S20>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 80; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_j[nSamps];
      }

      for (nSamps = 0; nSamps < 80 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_j[(i + nSamps) + 1]
          * projeto_DW.DigitalFilter_states_kc[nSamps];
      }

      projeto_B.DigitalFilter_d[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 80; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 81; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_j[nSamps];
      }

      projeto_B.DigitalFilter_d[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 80; i++) {
      projeto_DW.DigitalFilter_states_kc[79 - i] = projeto_B.DigitalFilter_o[i +
        944];
    }

    /* End of DiscreteFir: '<S20>/Digital Filter' */

    /* Delay: '<S2>/Delay2' */
    memcpy(&projeto_B.Abs3[0], &projeto_DW.Delay2_DSTATE[0], 24U * sizeof(real_T));
    memcpy(&projeto_B.Abs3[24], &projeto_B.DigitalFilter_d[0], 1000U * sizeof
           (real_T));

    /* Abs: '<S2>/Abs2' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs2' */

    /* S-Function (sdspbiquad): '<S11>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050790700054787071 * projeto_B.Abs3[uyIdx] -
                       -1.9923461255118937 *
                       projeto_DW.DigitalFilter_FILT_STATES_k[0]) -
        0.99437775351408519 * projeto_DW.DigitalFilter_FILT_STATES_k[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_k[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_k[1];
      projeto_DW.DigitalFilter_FILT_STATES_k[1] =
        projeto_DW.DigitalFilter_FILT_STATES_k[0];
      projeto_DW.DigitalFilter_FILT_STATES_k[0] = rtb_count_out;
      rtb_count_out = (0.00028459697566485996 * numAccum - -1.9835723983392863 *
                       projeto_DW.DigitalFilter_FILT_STATES_k[2]) -
        0.98471078624194563 * projeto_DW.DigitalFilter_FILT_STATES_k[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_k[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_k[3];
      projeto_DW.DigitalFilter_FILT_STATES_k[3] =
        projeto_DW.DigitalFilter_FILT_STATES_k[2];
      projeto_DW.DigitalFilter_FILT_STATES_k[2] = rtb_count_out;
      rtb_count_out = (6.3472708451233148E-5 * numAccum - -1.9789143415593364 *
                       projeto_DW.DigitalFilter_FILT_STATES_k[4]) -
        0.97916823239314155 * projeto_DW.DigitalFilter_FILT_STATES_k[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_k[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_k[5];
      projeto_DW.DigitalFilter_FILT_STATES_k[5] =
        projeto_DW.DigitalFilter_FILT_STATES_k[4];
      projeto_DW.DigitalFilter_FILT_STATES_k[4] = rtb_count_out;
      projeto_B.DigitalFilter_j[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S11>/Digital Filter' */

    /* DiscreteFir: '<S21>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 80; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_aj[nSamps];
      }

      for (nSamps = 0; nSamps < 80 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_aj[(i + nSamps) +
          1] * projeto_DW.DigitalFilter_states_mc[nSamps];
      }

      projeto_B.DigitalFilter_a[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 80; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 81; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_aj[nSamps];
      }

      projeto_B.DigitalFilter_a[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 80; i++) {
      projeto_DW.DigitalFilter_states_mc[79 - i] = projeto_B.DigitalFilter_o[i +
        944];
    }

    /* End of DiscreteFir: '<S21>/Digital Filter' */

    /* Delay: '<S2>/Delay3' */
    memcpy(&projeto_B.Abs3[0], &projeto_DW.Delay3_DSTATE[0], 24U * sizeof(real_T));
    memcpy(&projeto_B.Abs3[24], &projeto_B.DigitalFilter_a[0], 1000U * sizeof
           (real_T));

    /* Abs: '<S2>/Abs' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs' */

    /* S-Function (sdspbiquad): '<S12>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_a[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_a[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_a[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_a[1];
      projeto_DW.DigitalFilter_FILT_STATES_a[1] =
        projeto_DW.DigitalFilter_FILT_STATES_a[0];
      projeto_DW.DigitalFilter_FILT_STATES_a[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_a[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_a[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_a[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_a[3];
      projeto_DW.DigitalFilter_FILT_STATES_a[3] =
        projeto_DW.DigitalFilter_FILT_STATES_a[2];
      projeto_DW.DigitalFilter_FILT_STATES_a[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_a[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_a[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_a[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_a[5];
      projeto_DW.DigitalFilter_FILT_STATES_a[5] =
        projeto_DW.DigitalFilter_FILT_STATES_a[4];
      projeto_DW.DigitalFilter_FILT_STATES_a[4] = rtb_count_out;
      projeto_B.DigitalFilter_l[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S12>/Digital Filter' */

    /* DiscreteFir: '<S22>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 72; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_p[nSamps];
      }

      for (nSamps = 0; nSamps < 72 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_p[(i + nSamps) + 1]
          * projeto_DW.DigitalFilter_states_i[nSamps];
      }

      projeto_B.DigitalFilter_dp[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 72; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 73; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_p[nSamps];
      }

      projeto_B.DigitalFilter_dp[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 72; i++) {
      projeto_DW.DigitalFilter_states_i[71 - i] = projeto_B.DigitalFilter_o[i +
        952];
    }

    /* End of DiscreteFir: '<S22>/Digital Filter' */

    /* Delay: '<S2>/Delay4' */
    memcpy(&projeto_B.Abs3[0], &projeto_DW.Delay4_DSTATE[0], 28U * sizeof(real_T));
    memcpy(&projeto_B.Abs3[28], &projeto_B.DigitalFilter_dp[0], 996U * sizeof
           (real_T));

    /* Abs: '<S2>/Abs1' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs1' */

    /* S-Function (sdspbiquad): '<S10>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_n[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_n[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_n[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_n[1];
      projeto_DW.DigitalFilter_FILT_STATES_n[1] =
        projeto_DW.DigitalFilter_FILT_STATES_n[0];
      projeto_DW.DigitalFilter_FILT_STATES_n[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_n[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_n[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_n[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_n[3];
      projeto_DW.DigitalFilter_FILT_STATES_n[3] =
        projeto_DW.DigitalFilter_FILT_STATES_n[2];
      projeto_DW.DigitalFilter_FILT_STATES_n[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_n[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_n[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_n[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_n[5];
      projeto_DW.DigitalFilter_FILT_STATES_n[5] =
        projeto_DW.DigitalFilter_FILT_STATES_n[4];
      projeto_DW.DigitalFilter_FILT_STATES_n[4] = rtb_count_out;
      projeto_B.DigitalFilter_nt[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S10>/Digital Filter' */

    /* DiscreteFir: '<S23>/Digital Filter' */
    /* Consume delay line and beginning of input samples */
    for (i = 0; i < 65; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < i + 1; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_jd[nSamps];
      }

      for (nSamps = 0; nSamps < 65 - i; nSamps++) {
        rtb_count_out += projeto_P.DigitalFilter_Coefficients_jd[(i + nSamps) +
          1] * projeto_DW.DigitalFilter_states_au[nSamps];
      }

      projeto_B.DigitalFilter_n_c[i] = rtb_count_out;
    }

    /* Consume remaining input samples */
    for (i = 65; i < 1024; i++) {
      rtb_count_out = 0.0;
      for (nSamps = 0; nSamps < 66; nSamps++) {
        rtb_count_out += projeto_B.DigitalFilter_o[i - nSamps] *
          projeto_P.DigitalFilter_Coefficients_jd[nSamps];
      }

      projeto_B.DigitalFilter_n_c[i] = rtb_count_out;
    }

    /* Update delay line for next frame */
    for (i = 0; i < 65; i++) {
      projeto_DW.DigitalFilter_states_au[64 - i] = projeto_B.DigitalFilter_o[i +
        959];
    }

    /* End of DiscreteFir: '<S23>/Digital Filter' */

    /* Delay: '<S2>/Delay5' */
    memcpy(&projeto_B.Abs3[0], &projeto_DW.Delay5_DSTATE[0], 31U * sizeof(real_T));
    memcpy(&projeto_B.Abs3[31], &projeto_B.DigitalFilter_n_c[0], 993U * sizeof
           (real_T));

    /* Abs: '<S2>/Abs3' */
    for (nSamps = 0; nSamps < 1024; nSamps++) {
      projeto_B.Abs3[nSamps] = fabs(projeto_B.Abs3[nSamps]);
    }

    /* End of Abs: '<S2>/Abs3' */

    /* S-Function (sdspbiquad): '<S13>/Digital Filter' */
    uyIdx = 0;
    for (i = 0; i < 1024; i++) {
      rtb_count_out = (0.00050842155641983328 * projeto_B.Abs3[uyIdx] -
                       -1.992341225548061 *
                       projeto_DW.DigitalFilter_FILT_STATES_px[0]) -
        0.99437491177374016 * projeto_DW.DigitalFilter_FILT_STATES_px[1];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_px[0] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_px[1];
      projeto_DW.DigitalFilter_FILT_STATES_px[1] =
        projeto_DW.DigitalFilter_FILT_STATES_px[0];
      projeto_DW.DigitalFilter_FILT_STATES_px[0] = rtb_count_out;
      rtb_count_out = (0.00028488466413024662 * numAccum - -1.9835635537655714 *
                       projeto_DW.DigitalFilter_FILT_STATES_px[2]) -
        0.98470309242209231 * projeto_DW.DigitalFilter_FILT_STATES_px[3];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_px[2] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_px[3];
      projeto_DW.DigitalFilter_FILT_STATES_px[3] =
        projeto_DW.DigitalFilter_FILT_STATES_px[2];
      projeto_DW.DigitalFilter_FILT_STATES_px[2] = rtb_count_out;
      rtb_count_out = (6.3536795565340246E-5 * numAccum - -1.9789036269021463 *
                       projeto_DW.DigitalFilter_FILT_STATES_px[4]) -
        0.97915777408440774 * projeto_DW.DigitalFilter_FILT_STATES_px[5];
      numAccum = (2.0 * projeto_DW.DigitalFilter_FILT_STATES_px[4] +
                  rtb_count_out) + projeto_DW.DigitalFilter_FILT_STATES_px[5];
      projeto_DW.DigitalFilter_FILT_STATES_px[5] =
        projeto_DW.DigitalFilter_FILT_STATES_px[4];
      projeto_DW.DigitalFilter_FILT_STATES_px[4] = rtb_count_out;
      projeto_B.DigitalFilter_p[uyIdx] = 0.89125093813374556 * numAccum;
      uyIdx++;
    }

    /* End of S-Function (sdspbiquad): '<S13>/Digital Filter' */

    /* MATLAB Function: '<S1>/Limiar' */
    /* MATLAB Function 'Bloco de Decis?o L?gica /Limiar': '<S8>:1' */
    /* '<S8>:1:4' */
    /* '<S8>:1:6' */
    /* '<S8>:1:7' */
    /* '<S8>:1:8' */
    /* '<S8>:1:9' */
    /* '<S8>:1:11' */
    /* '<S8>:1:12' */
    /* '<S8>:1:13' */
    /* '<S8>:1:14' */
    /*  saidas */
    /* '<S8>:1:17' */
    for (i = 0; i < 1024; i++) {
      rtb_yl1[i] = (projeto_B.DigitalFilter_h[i] > 0.1);
    }

    /* End of MATLAB Function: '<S1>/Limiar' */
    /* '<S8>:1:18' */
    /* '<S8>:1:19' */
    /* '<S8>:1:20' */
    /* '<S8>:1:21' */
    /* '<S8>:1:22' */
    /* '<S8>:1:23' */
    /* '<S8>:1:24' */

    /* MATLAB Function: '<S1>/Identificador de Teclas' */
    /* MATLAB Function 'Bloco de Decis?o L?gica /Identificador de Teclas': '<S7>:1' */
    /* '<S7>:1:4' */
    for (i = 0; i < 1024; i++) {
      /* '<S7>:1:4' */
      /*  Duas linhas ativadas ERRO1 */
      /* '<S7>:1:40' */
      rtb_digito = 0.0;

      /* '<S7>:1:4' */
    }

    /* End of MATLAB Function: '<S1>/Identificador de Teclas' */
  }

  /* RateTransition: '<S1>/Rate Transition' */
  rtb_RateTransition =
    projeto_DW.RateTransition_Buffer[projeto_DW.RateTransition_ActiveBufIdx];

  /* MATLAB Function: '<S1>/Decis?o' incorporates:
   *  Memory: '<S1>/Memoria contador'
   *  Memory: '<S1>/Memoria prox digito'
   */
  /* MATLAB Function 'Bloco de Decis?o L?gica /Decis?o': '<S6>:1' */
  /* '<S6>:1:4' */
  /*  Numero de amostras equivalente a 20 ms. */
  if (rtb_RateTransition == projeto_DW.Memoriaproxdigito_PreviousInput) {
    /* '<S6>:1:6' */
    /* '<S6>:1:7' */
    rtb_count_out = projeto_DW.Memoriacontador_PreviousInput + 1.0;
  } else {
    /* '<S6>:1:9' */
    rtb_count_out = 0.0;
  }

  if (projeto_DW.Memoriacontador_PreviousInput >= 89.0) {
    /* '<S6>:1:12' */
    /* '<S6>:1:13' */
    rtb_dig_out = rtb_RateTransition;
  } else {
    /* '<S6>:1:15' */
    rtb_dig_out = 0.0;

    /*  Vazio */
  }

  /* '<S6>:1:18' */
  if (projeto_M->Timing.TaskCounters.TID[2] == 0) {
    /* Update for Delay: '<S2>/Delay' */
    memcpy(&projeto_DW.Delay_DSTATE[0], &projeto_B.DigitalFilter_k[1012], 12U *
           sizeof(real_T));

    /* Update for Delay: '<S2>/Delay1' */
    for (i = 0; i < 5; i++) {
      projeto_DW.Delay1_DSTATE[i] = projeto_B.DigitalFilter_h_m[i + 1019];
    }

    for (i = 0; i < 24; i++) {
      /* Update for Delay: '<S2>/Delay2' */
      projeto_DW.Delay2_DSTATE[i] = projeto_B.DigitalFilter_d[i + 1000];

      /* Update for Delay: '<S2>/Delay3' */
      projeto_DW.Delay3_DSTATE[i] = projeto_B.DigitalFilter_a[i + 1000];
    }

    /* End of Update for Delay: '<S2>/Delay1' */

    /* Update for Delay: '<S2>/Delay4' */
    memcpy(&projeto_DW.Delay4_DSTATE[0], &projeto_B.DigitalFilter_dp[996], 28U *
           sizeof(real_T));

    /* Update for Delay: '<S2>/Delay5' */
    memcpy(&projeto_DW.Delay5_DSTATE[0], &projeto_B.DigitalFilter_n_c[993], 31U *
           sizeof(real_T));

    /* Update for RateTransition: '<S1>/Rate Transition' */
    projeto_DW.RateTransition_Buffer[projeto_DW.RateTransition_ActiveBufIdx == 0]
      = rtb_digito;
    projeto_DW.RateTransition_ActiveBufIdx = (int8_T)
      (projeto_DW.RateTransition_ActiveBufIdx == 0);
  }

  /* Update for Memory: '<S1>/Memoria prox digito' incorporates:
   *  MATLAB Function: '<S1>/Decis?o'
   */
  projeto_DW.Memoriaproxdigito_PreviousInput = rtb_RateTransition;

  /* Update for Memory: '<S1>/Memoria contador' */
  projeto_DW.Memoriacontador_PreviousInput = rtb_count_out;

  /* Matfile logging */
  rt_UpdateTXYLogVars(projeto_M->rtwLogInfo, (&projeto_M->Timing.taskTime0));

  /* signal main to stop simulation */
  {                                    /* Sample time: [2.2675736961451248E-5s, 0.0s] */
    if ((rtmGetTFinal(projeto_M)!=-1) &&
        !((rtmGetTFinal(projeto_M)-projeto_M->Timing.taskTime0) >
          projeto_M->Timing.taskTime0 * (DBL_EPSILON))) {
      rtmSetErrorStatus(projeto_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++projeto_M->Timing.clockTick0)) {
    ++projeto_M->Timing.clockTickH0;
  }

  projeto_M->Timing.taskTime0 = projeto_M->Timing.clockTick0 *
    projeto_M->Timing.stepSize0 + projeto_M->Timing.clockTickH0 *
    projeto_M->Timing.stepSize0 * 4294967296.0;
  rate_scheduler();
}

/* Model initialize function */
void projeto_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)projeto_M, 0,
                sizeof(RT_MODEL_projeto_T));
  rtmSetTFinal(projeto_M, -1);
  projeto_M->Timing.stepSize0 = 2.2675736961451248E-5;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    projeto_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(projeto_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(projeto_M->rtwLogInfo, (NULL));
    rtliSetLogT(projeto_M->rtwLogInfo, "");
    rtliSetLogX(projeto_M->rtwLogInfo, "");
    rtliSetLogXFinal(projeto_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(projeto_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(projeto_M->rtwLogInfo, 0);
    rtliSetLogMaxRows(projeto_M->rtwLogInfo, 1000);
    rtliSetLogDecimation(projeto_M->rtwLogInfo, 1);
    rtliSetLogY(projeto_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(projeto_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(projeto_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &projeto_B), 0,
                sizeof(B_projeto_T));

  /* states (dwork) */
  (void) memset((void *)&projeto_DW, 0,
                sizeof(DW_projeto_T));

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(projeto_M->rtwLogInfo, 0.0, rtmGetTFinal
    (projeto_M), projeto_M->Timing.stepSize0, (&rtmGetErrorStatus(projeto_M)));

  {
    char_T *sErr;

    /* Start for S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
    sErr = GetErrorBuffer(&projeto_DW.FromMultimediaFile_HostLib[0U]);
    CreateHostLibrary("libmwfrommmfile.so",
                      &projeto_DW.FromMultimediaFile_HostLib[0U]);
    createAudioInfo(&projeto_DW.FromMultimediaFile_AudioInfo[0U], 1U, 0U,
                    44100.0, 16, 1, 1024, 0, 0);
    createVideoInfo(&projeto_DW.FromMultimediaFile_VideoInfo[0U], 0U, 0.0, 0.0,
                    "", 0, 0, 0, 0, 1U, 0, 0, 0);
    if (*sErr == 0) {
      LibCreate_FromMMFile(&projeto_DW.FromMultimediaFile_HostLib[0U], 0,
                           "/home/yan.m/PSD/PSD-detector-dtmf/dtmf_2_65.wav",
                           "/opt/MATLAB/R2015a/toolbox/shared/multimedia/bin/glnxa64/audio/libmwaudiofilesndfilereaderplugin.so",
                           "/opt/MATLAB/R2015a/toolbox/shared/multimedia/bin/glnxa64/audioslconverter",
                           &projeto_DW.FromMultimediaFile_AudioInfo[0U],
                           &projeto_DW.FromMultimediaFile_VideoInfo[0U], 0U, 1U,
                           1U, 0U, 0U);
    }

    if (*sErr == 0) {
      LibStart(&projeto_DW.FromMultimediaFile_HostLib[0U]);
    }

    if (*sErr != 0) {
      DestroyHostLibrary(&projeto_DW.FromMultimediaFile_HostLib[0U]);
      if (*sErr != 0) {
        rtmSetErrorStatus(projeto_M, sErr);
        rtmSetStopRequested(projeto_M, 1);
      }
    }

    /* End of Start for S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
  }

  {
    int32_T i;

    /* InitializeConditions for S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
    LibReset(&projeto_DW.FromMultimediaFile_HostLib[0U]);

    /* InitializeConditions for S-Function (sdsprandsrc2): '<S45>/Random Source' */
    projeto_DW.RandomSource_SEED_DWORK = projeto_P.UniformNoiseGenerator_seed;
    RandSrcInitState_U_64(&projeto_DW.RandomSource_SEED_DWORK,
                          projeto_DW.RandomSource_STATE_DWORK, 1);

    /* InitializeConditions for Buffer: '<S3>/Buffer' */
    for (i = 0; i < 2048; i++) {
      projeto_DW.Buffer_CircBuf[i] = projeto_P.Buffer_ic;
    }

    projeto_DW.Buffer_inBufPtrIdx = 1024;
    projeto_DW.Buffer_bufferLength = 1024;
    projeto_DW.Buffer_outBufPtrIdx = 0;

    /* End of InitializeConditions for Buffer: '<S3>/Buffer' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S46>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S46>/Digital Filter' */

    /* InitializeConditions for DownSample: '<S4>/Downsample' */
    projeto_DW.Downsample_Count = 0;
    projeto_DW.Downsample_InBufIdx = 0;
    for (i = 0; i < 1024; i++) {
      projeto_DW.Downsample_Buffer[i] = projeto_P.Downsample_ic;
    }

    /* End of InitializeConditions for DownSample: '<S4>/Downsample' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S19>/Digital Filter' */
    projeto_DW.DigitalFilter_FILT_STATES_o[0] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_o[1] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_o[2] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_o[3] = 0.0;

    /* InitializeConditions for DiscreteFir: '<S24>/Digital Filter' */
    for (i = 0; i < 104; i++) {
      projeto_DW.DigitalFilter_states[i] = projeto_P.DigitalFilter_InitialStates;
    }

    /* End of InitializeConditions for DiscreteFir: '<S24>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay' */
    for (i = 0; i < 12; i++) {
      projeto_DW.Delay_DSTATE[i] = projeto_P.Delay_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S15>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_i[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S15>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S25>/Digital Filter' */
    for (i = 0; i < 127; i++) {
      projeto_DW.DigitalFilter_states_k[i] =
        projeto_P.DigitalFilter_InitialStates_k;
    }

    /* End of InitializeConditions for DiscreteFir: '<S25>/Digital Filter' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S16>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_p[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S16>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S9>/Digital Filter' */
    for (i = 0; i < 127; i++) {
      projeto_DW.DigitalFilter_states_m[i] =
        projeto_P.DigitalFilter_InitialStates_h;
    }

    /* End of InitializeConditions for DiscreteFir: '<S9>/Digital Filter' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S14>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_m[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S14>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S26>/Digital Filter' */
    for (i = 0; i < 117; i++) {
      projeto_DW.DigitalFilter_states_a[i] =
        projeto_P.DigitalFilter_InitialStates_hr;
    }

    /* End of InitializeConditions for DiscreteFir: '<S26>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay1' */
    for (i = 0; i < 5; i++) {
      projeto_DW.Delay1_DSTATE[i] = projeto_P.Delay1_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay1' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S17>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_m4[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S17>/Digital Filter' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S18>/Digital Filter' */
    projeto_DW.DigitalFilter_FILT_STATES_d[0] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_d[1] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_d[2] = 0.0;
    projeto_DW.DigitalFilter_FILT_STATES_d[3] = 0.0;

    /* InitializeConditions for DiscreteFir: '<S20>/Digital Filter' */
    for (i = 0; i < 80; i++) {
      projeto_DW.DigitalFilter_states_kc[i] =
        projeto_P.DigitalFilter_InitialStates_f;
    }

    /* End of InitializeConditions for DiscreteFir: '<S20>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay2' */
    for (i = 0; i < 24; i++) {
      projeto_DW.Delay2_DSTATE[i] = projeto_P.Delay2_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay2' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S11>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_k[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S11>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S21>/Digital Filter' */
    for (i = 0; i < 80; i++) {
      projeto_DW.DigitalFilter_states_mc[i] =
        projeto_P.DigitalFilter_InitialStates_b;
    }

    /* End of InitializeConditions for DiscreteFir: '<S21>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay3' */
    for (i = 0; i < 24; i++) {
      projeto_DW.Delay3_DSTATE[i] = projeto_P.Delay3_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay3' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S12>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_a[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S12>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S22>/Digital Filter' */
    for (i = 0; i < 72; i++) {
      projeto_DW.DigitalFilter_states_i[i] =
        projeto_P.DigitalFilter_InitialStates_j;
    }

    /* End of InitializeConditions for DiscreteFir: '<S22>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay4' */
    for (i = 0; i < 28; i++) {
      projeto_DW.Delay4_DSTATE[i] = projeto_P.Delay4_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay4' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S10>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_n[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S10>/Digital Filter' */

    /* InitializeConditions for DiscreteFir: '<S23>/Digital Filter' */
    for (i = 0; i < 65; i++) {
      projeto_DW.DigitalFilter_states_au[i] =
        projeto_P.DigitalFilter_InitialStates_br;
    }

    /* End of InitializeConditions for DiscreteFir: '<S23>/Digital Filter' */

    /* InitializeConditions for Delay: '<S2>/Delay5' */
    for (i = 0; i < 31; i++) {
      projeto_DW.Delay5_DSTATE[i] = projeto_P.Delay5_InitialCondition;
    }

    /* End of InitializeConditions for Delay: '<S2>/Delay5' */

    /* InitializeConditions for S-Function (sdspbiquad): '<S13>/Digital Filter' */
    for (i = 0; i < 6; i++) {
      projeto_DW.DigitalFilter_FILT_STATES_px[i] = 0.0;
    }

    /* End of InitializeConditions for S-Function (sdspbiquad): '<S13>/Digital Filter' */

    /* InitializeConditions for RateTransition: '<S1>/Rate Transition' */
    projeto_DW.RateTransition_Buffer[0] = projeto_P.RateTransition_X0;

    /* InitializeConditions for Memory: '<S1>/Memoria prox digito' */
    projeto_DW.Memoriaproxdigito_PreviousInput = projeto_P.Memoriaproxdigito_X0;

    /* InitializeConditions for Memory: '<S1>/Memoria contador' */
    projeto_DW.Memoriacontador_PreviousInput = projeto_P.Memoriacontador_X0;
  }
}

/* Model terminate function */
void projeto_terminate(void)
{
  char_T *sErr;

  /* Terminate for S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
  sErr = GetErrorBuffer(&projeto_DW.FromMultimediaFile_HostLib[0U]);
  LibTerminate(&projeto_DW.FromMultimediaFile_HostLib[0U]);
  if (*sErr != 0) {
    rtmSetErrorStatus(projeto_M, sErr);
    rtmSetStopRequested(projeto_M, 1);
  }

  LibDestroy(&projeto_DW.FromMultimediaFile_HostLib[0U], 0);
  DestroyHostLibrary(&projeto_DW.FromMultimediaFile_HostLib[0U]);

  /* End of Terminate for S-Function (sdspwmmfi2): '<S3>/From Multimedia File' */
}
