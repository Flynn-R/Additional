#include "source.h"

int main()
{
    // Задание 1
    {
        cout << "Task 1" << endl;

        thread th1(pcout);
        thread th2(pcout);
        th1.join();
        th2.join();

        cout << endl;
    }

    // Задание 2
    {
        cout << "Task 2" << endl;

        cout << "Beginning calculations..." << endl;
        this_thread::sleep_for(5s);

        size_t progress;
        size_t i = 100'000;
        size_t result;
        
        thread prime_calc([&](){ result = prime(i, progress); });
        
        float percentage = 0;
        while(percentage != 100)
        {
            this_thread::sleep_for(1s);
            percentage = (static_cast<float>(progress) / i) * 100;
            system("cls");
            cout << "Progress: " << percentage << "%" << endl;
        }
        prime_calc.join();
        cout << i << "'s prime number is " << result << endl << endl;
    }

    // Задание 3
    {
        cout << "Task 3" << endl;

        vector<int> items;
        
        thread own(owner, ref(items));
        thread thf(thief, ref(items));
        own.detach();
        thf.detach();
        
        size_t stop = 0;
        while(stop != 30)
        {
            this_thread::sleep_for(1s);
            
            print(items);
            ++stop;
        }
        cout << "Final items: ";
        print(items);
    }

    return 0;
}
