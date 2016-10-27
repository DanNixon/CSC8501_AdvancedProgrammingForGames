Command Line Interface Reference
================================

TODO

`inject_error [input filename] [output_filename]`

Used to inject error into an encoded bit stream using the algorithm described in
the coursework 2 specification.

`decode [trellis_filename] [input_filename] [output_filename]`

Decodes an encoded bit stream using a trellis.

`compare_decoded [original_filename] [clean_filename] [noisy_filename]`

Utility to compare two decoded bit streams with the original before encoded,
used to test decoding in absence and presence of noise.
