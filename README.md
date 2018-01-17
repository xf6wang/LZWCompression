# LZWCompression
A lossless data compression tool written in C++ that implements the Lempel–Ziv–Welch algorithm. 

## Build
```
git clone *repository*  
cd LZWCompression  
make  
```

encoder and decoder can be built individually:
```
make encoder  
make decoder  
```

## Run
```
./encode sample.txt output.bin  
./decode output.bin result.txt  
```

## Algorithms & Optimizations
An explaination of the algorithm and forward moving entries using frequency analysis can be found on xf6wang.github.io
