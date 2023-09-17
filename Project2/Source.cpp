#include <vector>
#include <thread>
#include <cstdlib>
#include <iostream>


const int n = 1000;

void fillMatr(std::vector<std::vector<int>>& A) {
    for (int i = 0; i < n; i++) {
        std::vector<int> buf;
        for (int j = 0; j < n; j++) {
            buf.push_back(rand() % 100);
        }
        A.push_back(buf);
    }

}

void show(std::vector<std::vector<int>> A) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << A[i][j] << " ";
        }
        std::cout << "\n";
    }

}
void multMatr(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B) {
    std::vector<std::vector<int>> C;

    for (int i = 0; i < n; i++) {
        std::vector<int> vec;
        for (int j = 0; j < n; j++) {
            int buf = 0;
            for (int k = 0; k < n; k++) {
                buf += A[i][k] * B[k][j];
            }
            vec.push_back(buf);
        }
        C.push_back(vec);
    }



}

std::vector<std::vector<int>> multMatrThread(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B, int thB, int thE) {
    std::vector<std::vector<int>> C;

    for (int i = thB; i < thE; i++) {
        std::vector<int> vec;
        for (int j = 0; j < n; j++) {
            int buf = 0;
            for (int k = 0; k < n; k++) {
                buf += A[i][k] * B[k][j];
            }
            vec.push_back(buf);
        }
        C.push_back(vec);
    }

    return C;
}

int main()
{
    std::vector<std::vector<int>>  A, B, C;
    fillMatr(A);
    fillMatr(B);

    auto start1 = std::chrono::system_clock::now();

    multMatr(A, B);

    auto end1 = std::chrono::system_clock::now();

    int th = std::thread::hardware_concurrency();
    C.clear();
    std::vector<std::thread> T;

    auto start2 = std::chrono::system_clock::now();

    for (int i = 0; i < n; i += n / th) {


        T.push_back(std::move(std::thread(multMatrThread, A, B, i, i + n / th)));
    }

    for (auto& thread : T) {
        thread.join();
    }

    auto end2 = std::chrono::system_clock::now();


    std::chrono::duration<double> r1 = end1 - start1;
    std::chrono::duration<double> r2 = end2 - start2;

   std::cout << "Time without threads: " << r1.count() << std::endl;
   std::cout << "Time with threads: " << r2.count();

}
