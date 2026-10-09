memory=524288  # 512MB
stack_size=524288  # 512MB

ulimit -v "${memory}"
ulimit -s "${stack_size}"

g++ main.cpp -DSTRESS -O2 -std=c++17 -Wno-unused-result -Wshadow -Wall -o main
g++ brute.cpp -DSTRESS -O2 -std=c++17 -Wno-unused-result -Wshadow -Wall -o brute
g++ gen.cpp -DSTRESS -O2 -std=c++17 -Wno-unused-result -o gen


for((i = 1; i <= 1000; ++i)); do {

    ./gen > test.in 
    ./main  < test.in > test.out
    ./brute < test.in > test.ans

    # External grading program:
    # checker > /dev/null || {
    # General:
    diff -Z test.out test.ans > /dev/null || {
        echo "WA on the following test:"
        cat test.in
        echo "=================="
        echo "Your answer is:"
        cat test.out
        echo "=================="
        echo "Correct answer is:"
        cat test.ans
        break
    }
    echo "Passed test: "  $i
}
done

rm main
rm gen
rm brute
