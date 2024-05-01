# Tools

## WavToBinary.py

This tool can be used to transform `.wav` files into `.bwav` files.

Important: `.wav` files need to have a sample rate of 22050Hz and a resolution
of 32-bit float.

To get songs with different tracks for each instrument/vocal one could use the website:
https://multitracksearch.cambridge-mt.com/ms-mtk-search.htm
On this website are multiple songs where each track is in a separate file.

## BinaryWavMerger.py

This tool merges multiple `.bwav` files into one.

## BinaryAudioViewer.py

This tool can be used to view the signal inside a `.bwav` file.
This can be useful when debugging certain files.

## FindBestR.py

This tool was used to find nice resistor values for the presentation slides.

## LtSpicePlotter.py

This tool can be used to make nicer plots the LtSpice data using matplotlib

## NandExperimentPlotter.py

This tool is used to visualize the data of the first nand gatter experiment.

## NandExperimentPlotter2.py

This tool is used to visualize the data of the second nand gatter experiment.

## SignalArrayCreator.py

This tool was used in the early stages to create an array which contains a simple signal like a sinus. This array can then directly be inserted into the code.

## WavToHeaderFile.py

This tool was used in the early stages to transform a `.wav` file to a header file containing an array with the signal data.
