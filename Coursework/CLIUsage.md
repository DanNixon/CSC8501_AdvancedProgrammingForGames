Command Line Interface Reference
================================

`help`

Shows help for the current command level.

`exit`

Exits the application.

`encoder components list`

Lists the components currently included in the encoder circuit.

`encoder components add [name] [id]`

Adds a component to the encoder circuit with unique id `id`.

`encoder components remove [id]`

Remove a component from the encoder circuit given its unique ID.

`encoder wires add [pin 1] [pin 2]`

Adds a wire between two pins.

Pins are defined as `[component id].[pin id]`.

`encoder wires remove [pin 1] [pin 2]`

Removes a wire between two pins.

`encoder permutations generate`

Generates permutations for the `cw_basic` encoder preset.

Permutation generation parameters are hard coded so this will not work for other
encoder configurations.

`encoder permutations list`

Lists the generated wiring permutations.

`encoder permutations load [permutation index]`

Loads a permutation into the active encoder given its index.

`encoder preset [preset name]`

Loads an encoder preset.

Valid presets are:
 - "cw_basic" (the least amount of wiring for an encoder, used as a base for
   permutation generation
 - "cw_example" (an equivalent encoder to the one in the coursework 1
   specification)

`encoder reset`

Resets the current encoder to one with an empty configuration.

`encoder show`

Outputs a textual representation of the current encoder configuration.

`encode [input filename] [output filename]`

Encodes the contents of the input file using the current encoder configuration
and saves the result in the output file given.

`compare [file 1] [file 2] (... [file n])`

Compares a number of files.

If only two files are specified the hamming distance between them is measured,
if multiple files are specified then they are all checked to see if they are
identical.

`find_matching [directory] [glob]`

Finds groups of matching datasets in files found in a directory that match a
given glob.

Groups are given as groups of indices in which all datasets in the group are
identical.

`inject_error [input filename] [output_filename]`

Used to inject error into an encoded bit stream using the algorithm described in
the coursework 2 specification.

`decode [trellis_filename] [input_filename] [output_filename]`

Decodes an encoded bit stream using a trellis.

`compare_decoded [original_filename] [clean_filename] [noisy_filename]`

Utility to compare two decoded bit streams with the original before encoded,
used to test decoding in absence and presence of noise.

`workflow [input filename] [output directory]`

Performs a workflow over all permutations of encoder wirings. Permutations must
have already been generated.

Workflow is:
 - permutation generation
 - clean encoding
 - trellis generation
 - clean decode
 - error injection
 - noisy decode
 - clean & noisy decode comparison to input data
