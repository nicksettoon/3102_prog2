#pragma once

namespace tools
{
    bool isPrime(int number_in)//Function to check if a number is Prime.
    {
        int factorcount=0;
        for(int i=1;i<=number_in;i++)
        {
            if(number_in%i==0)
                factorcount++;
        }
        if(factorcount==2)//Prime no.has 2 factors-1 and number itself.
            return 1;
        else
            return 0;
    }

    int getNextPrime(int number_in)
    {
        std::cout << "getting next prime number after " << number_in << std::endl;
        int primeout=0;

        for(int i = number_in;;i++)//No end limit as when prime is found we will break the loop.
        {
            if(isPrime(i))
            {
                primeout=i;
                break;
            }
        }
        std::cout <<"Next prime number is: " << primeout << std::endl;
        return primeout;
    };
}