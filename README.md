# normtools

Normtools is a grwoing collection of max msp externals based on normal distribution sampling. those tools are written in C and use max-sdk.

## The tools
At the moment the collection comprises 3 externals: norm, norm_random_note, norm_rhythm

### norm
A simple normal disrtibution sampling, left inlet for mu and bang, right inlet for sigma.

### norm_random_note
An harmonic arpeggiator that outputs random midi note based on the input note, according to the distribution of its harmonics. inputs are: midi note(or bang), offset, variance.

### norm_rhythm
A rhythm generator that skips a random number of ticks of the input. Inputs are clock, mu and sigma. 

## Building
To build normtools first download max-sdk, then add the normtools folder to the source folder in the max-sdk package and build as described in the max-sdk documentation.

## external links
max-sdk: https://github.com/Cycling74/max-sdk
