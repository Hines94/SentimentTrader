mkdir build
cd build

cmake .. || exit 1
make || exit 1
./SentimentTrader