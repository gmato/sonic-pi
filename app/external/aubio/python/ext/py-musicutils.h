#ifndef PY_AUBIO_MUSICUTILS_H
#define PY_AUBIO_MUSICUTILS_H

static char Py_aubio_window_doc[] = ""
"window(window_type, size)\n"
"\n"
"Create a window of length `size`. `window_type` should be one\n"
"of the following:\n"
"\n"
"- `default` (same as `hanningz`).\n"
"- `ones`\n"
"- `rectangle`\n"
"- `hamming`\n"
"- `hanning`\n"
"- `hanningz` [1]_\n"
"- `blackman`\n"
"- `blackman_harris`\n"
"- `gaussian`\n"
"- `welch`\n"
"- `parzen`\n"
"\n"
"Parameters\n"
"----------\n"
"window_type : str\n"
"   Type of window.\n"
"size : int\n"
"   Length of window.\n"
"\n"
"Returns\n"
"-------\n"
"fvec\n"
"   Array of shape `(length,)` containing the new window.\n"
"\n"
"See Also\n"
"--------\n"
"pvoc, fft\n"
"\n"
"Examples\n"
"--------\n"
"Compute a zero-phase Hann window on `1024` points:\n"
"\n"
">>> aubio.window('hanningz', 1024)\n"
"array([  0.00000000e+00,   9.41753387e-06,   3.76403332e-05, ...,\n"
"         8.46982002e-05,   3.76403332e-05,   9.41753387e-06], dtype=float32)\n"
"\n"
"Plot different window types with `matplotlib <https://matplotlib.org/>`_:\n"
"\n"
">>> import matplotlib.pyplot as plt\n"
">>> modes = ['default', 'ones', 'rectangle', 'hamming', 'hanning',\n"
"...          'hanningz', 'blackman', 'blackman_harris', 'gaussian',\n"
"...          'welch', 'parzen']; n = 2048\n"
">>> for m in modes: plt.plot(aubio.window(m, n), label=m)\n"
"...\n"
">>> plt.legend(); plt.show()\n"
"\n"
"Note\n"
"----\n"
"The following examples contain the equivalent source code to compute\n"
"each type of window with `NumPy <https://numpy.org>`_:\n"
"\n"
">>> n = 1024; x = np.arange(n, dtype=aubio.float_type)\n"
">>> ones = np.ones(n).astype(aubio.float_type)\n"
">>> rectangle = 0.5 * ones\n"
">>> hanning = 0.5 - 0.5 * np.cos(2 * np.pi * x / n)\n"
">>> hanningz = 0.5 * (1 - np.cos(2 * np.pi * x / n))\n"
">>> hamming = 0.54 - 0.46 * np.cos(2.*np.pi * x / (n - 1))\n"
">>> blackman = 0.42 \\\n"
"...          - 0.50 * np.cos(2 * np.pi * x / (n - 1)) \\\n"
"...          + 0.08 * np.cos(4 * np.pi * x / (n - 1))\n"
">>> blackman_harris = 0.35875 \\\n"
"...       - 0.48829 * np.cos(2 * np.pi * x / (n - 1)) \\\n"
"...       + 0.14128 * np.cos(4 * np.pi * x / (n - 1)) \\\n"
"...       + 0.01168 * np.cos(6 * np.pi * x / (n - 1))\n"
">>> gaussian = np.exp( - 0.5 * ((x - 0.5 * (n - 1)) \\\n"
"...                            / (0.25 * (n - 1)) )**2 )\n"
">>> welch = 1 - ((2 * x - n) / (n + 1))**2\n"
">>> parzen = 1 - np.abs((2 * x - n) / (n + 1))\n"
">>> default = hanningz\n"
"References\n"
"----------\n"
#if 0
"`Window function <https://en.wikipedia.org/wiki/Window_function>`_ on\n"
"Wikipedia.\n"
"\n"
#endif
".. [1] Amalia de Götzen, Nicolas Bernardini, and Daniel Arfib. Traditional\n"
"   (?) implementations of a phase vocoder: the tricks of the trade.\n"
"   In *Proceedings of the International Conference on Digital Audio\n"
"   Effects* (DAFx-00), pages 37–44, University of Verona, Italy, 2000.\n"
"   (`online version <"
"https://www.cs.princeton.edu/courses/archive/spr09/cos325/Bernardini.pdf"
">`_).\n"
"";

PyObject * Py_aubio_window(PyObject *self, PyObject *args);

static char Py_aubio_level_lin_doc[] = ""
"level_lin(x)\n"
"\n"
"Compute sound pressure level of `x`, on a linear scale.\n"
"\n"
"Parameters\n"
"----------\n"
"x : fvec\n"
"   input vector\n"
"\n"
"Returns\n"
"-------\n"
"float\n"
"   Linear level of `x`.\n"
"\n"
"Example\n"
"-------\n"
"\n"
">>> aubio.level_lin(aubio.fvec(numpy.ones(1024)))\n"
"1.0\n"
"\n"
"Note\n"
"----\n"
"Computed as the average of the squared amplitudes:\n"
"\n"
".. math:: L = \\frac {\\sum_{n=0}^{N-1} {x_n}^2} {N}\n"
"\n"
"See Also\n"
"--------\n"
"db_spl, silence_detection, level_detection\n"
"";

PyObject * Py_aubio_level_lin(PyObject *self, PyObject *args);

static char Py_aubio_db_spl_doc[] = ""
"db_spl(x)\n"
"\n"
"Compute Sound Pressure Level (SPL) of `x`, in dB.\n"
"\n"
"Parameters\n"
"----------\n"
"x : fvec\n"
"   input vector\n"
"\n"
"Returns\n"
"-------\n"
"float\n"
"   Level of `x`, in dB SPL.\n"
"\n"
"Example\n"
"-------\n"
"\n"
">>> aubio.db_spl(aubio.fvec(np.ones(1024)))\n"
"1.0\n"
">>> aubio.db_spl(0.7*aubio.fvec(np.ones(32)))\n"
"-3.098040819168091\n"
"\n"
"Note\n"
"----\n"
"Computed as `log10` of :py:func:`level_lin`:\n"
"\n"
".. math::\n"
"\n"
"   {SPL}_{dB} = log10{\\frac {\\sum_{n=0}^{N-1}{x_n}^2} {N}}\n"
"\n"
"This quantity is often incorrectly called 'loudness'.\n"
"\n"
"See Also\n"
"--------\n"
"level_lin, silence_detection, level_detection\n"
"";

PyObject * Py_aubio_db_spl(PyObject *self, PyObject *args);

static char Py_aubio_silence_detection_doc[] = ""
"silence_detection(vec, level)\n"
"\n"
"Check if level of `vec`, in dB SPL, is under a given threshold.\n"
"\n"
"Parameters\n"
"----------\n"
"vec : fvec\n"
"   input vector\n"
"level : float\n"
"   level threshold, in dB SPL\n"
"\n"
"Returns\n"
"-------\n"
"int\n"
"   `1` if level of `vec`, in dB SPL, is under `level`,\n"
"   `0` otherwise.\n"
"\n"
"Examples\n"
"--------\n"
"\n"
">>> aubio.silence_detection(aubio.fvec(32), -100.)\n"
"1\n"
">>> aubio.silence_detection(aubio.fvec(np.ones(32)), 0.)\n"
"0\n"
"\n"
"See Also\n"
"--------\n"
"level_detection, db_spl, level_lin\n"
"";

PyObject * Py_aubio_silence_detection(PyObject *self, PyObject *args);

static char Py_aubio_level_detection_doc[] = ""
"level_detection(vec, level)\n"
"\n"
"Check if `vec` is above threshold `level`, in dB SPL.\n"
"\n"
"Parameters\n"
"----------\n"
"vec : fvec\n"
"   input vector\n"
"level : float\n"
"   level threshold, in dB SPL\n"
"\n"
"Returns\n"
"-------\n"
"float\n"
"   `1.0` if level of `vec` in dB SPL is under `level`,\n"
"   `db_spl(vec)` otherwise.\n"
"\n"
"Example\n"
"-------\n"
"\n"
">>> aubio.level_detection(0.7*aubio.fvec(np.ones(1024)), -3.)\n"
"1.0\n"
">>> aubio.level_detection(0.7*aubio.fvec(np.ones(1024)), -4.)\n"
"-3.0980708599090576\n"
"\n"
"See Also\n"
"--------\n"
"silence_detection, db_spl, level_lin\n"
"";

PyObject * Py_aubio_level_detection(PyObject *self, PyObject *args);

static char Py_aubio_shift_doc[] = ""
"shift(vec)\n"
"\n"
"Swap left and right partitions of a vector, in-place.\n"
"\n"
"Parameters\n"
"----------\n"
"vec : fvec\n"
"   input vector to shift\n"
"\n"
"Returns\n"
"-------\n"
"fvec\n"
"   The swapped vector.\n"
"\n"
"Notes\n"
"-----\n"
"The input vector is also modified.\n"
"\n"
"For a vector of length N, the partition is split at index N - N//2.\n"
"\n"
"Example\n"
"-------\n"
"\n"
">>> aubio.shift(aubio.fvec(np.arange(3)))\n"
"array([2., 0., 1.], dtype=" AUBIO_NPY_SMPL_STR ")\n"
"\n"
"See Also\n"
"--------\n"
"ishift\n"
"";
PyObject * Py_aubio_shift(PyObject *self, PyObject *args);

static char Py_aubio_ishift_doc[] = ""
"ishift(vec)\n"
"\n"
"Swap right and left partitions of a vector, in-place.\n"
"\n"
"Parameters\n"
"----------\n"
"vec : fvec\n"
"   input vector to shift\n"
"\n"
"Returns\n"
"-------\n"
"fvec\n"
"   The swapped vector.\n"
"\n"
"Notes\n"
"-----\n"
"The input vector is also modified.\n"
"\n"
"Unlike with :py:func:`shift`, the partition is split at index N//2.\n"
"\n"
"Example\n"
"-------\n"
"\n"
">>> aubio.ishift(aubio.fvec(np.arange(3)))\n"
"array([1., 2., 0.], dtype=" AUBIO_NPY_SMPL_STR ")\n"
"\n"
"See Also\n"
"--------\n"
"shift\n"
"";
PyObject * Py_aubio_ishift(PyObject *self, PyObject *args);

static char Py_aubio_hztomel_doc[] = ""
"hztomel(f, htk=False)\n"
"\n"
"Convert a scalar from frequency to mel scale.\n"
"\n"
"Parameters\n"
"----------\n"
"m : float\n"
"   input frequency, in Hz\n"
"htk : bool\n"
"   if `True`, use Htk mel scale instead of Slaney.\n"
"\n"
"Returns\n"
"-------\n"
"float\n"
"   output mel\n"
"\n"
"See Also\n"
"--------\n"
"meltohz\n"
"";
PyObject * Py_aubio_hztomel(PyObject *self, PyObject *args);

static char Py_aubio_meltohz_doc[] = ""
"meltohz(m, htk=False)\n"
"\n"
"Convert a scalar from mel scale to frequency.\n"
"\n"
"Parameters\n"
"----------\n"
"m : float\n"
"   input mel\n"
"htk : bool\n"
"   if `True`, use Htk mel scale instead of Slaney.\n"
"\n"
"Returns\n"
"-------\n"
"float\n"
"   output frequency, in Hz\n"
"\n"
"See Also\n"
"--------\n"
"hztomel\n"
"";
PyObject * Py_aubio_meltohz(PyObject *self, PyObject *args);

static char Py_aubio_hztomel_htk_doc[] = ""
"hztomel_htk(m)\n"
"\n"
"Same as `hztomel(m, htk=True)`\n"
"\n"
"See Also\n"
"--------\n"
"hztomel\n"
"";
PyObject * Py_aubio_hztomel_htk(PyObject *self, PyObject *args);

static char Py_aubio_meltohz_htk_doc[] = ""
"meltohz_htk(m)\n"
"\n"
"Same as `meltohz(m, htk=True)`\n"
"\n"
"See Also\n"
"--------\n"
"meltohz\n"
"";
PyObject * Py_aubio_meltohz_htk(PyObject *self, PyObject *args);

#endif /* PY_AUBIO_MUSICUTILS_H */