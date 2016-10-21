# Design Choices

## Inheritance structure

A polymorphic structure for the circuit simulation portion of the encoder was
used to allow more complex encoders to easily be created.

If sticking strictly to the design reuirements then the encoder could be
implemented in a much simpler manner that would not allow such expansion,
however would be much more computationally and memory optimal.

## Data type

I did consider making the circuit simulator templated to allow devices to
operate on any type, however since the devices used in the design constraints
all operate on digital logic the ```bool``` type was used and templating was
not used in the circuit simulator.

In a more tightly integrated solution bits coud be represented as individual
bits of an array of ```uint8_t``` of sufficient length, this becomes more
difficult to accomplish under the polymorphic design for circuit devices.

## Circuit validation

Validation of the circuit is implemented that ensures the circuit wiring allows
the circuit to be evaluated, i.e. there are no recursive connections which will
in turn create an infinate recursive loop when evaluating the circuit.

This validation is done using a depth first traversal of the circuit starting
from the output bus.
