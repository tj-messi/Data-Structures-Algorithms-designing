#include <iostream>
#include <cmath>
 
bool IsPrime(int x)
{
    if (x == 1)
        return false;
    if (x == 2)
        return true;
    for (int k = 2; k <= int(sqrt(x)); k++)
        if (x % k == 0)
            return false;
    return true;
}
 
void UpdateP(int& P)
{
    while (true)
    {
        if (IsPrime(P))
            break;
        P++;
    }
}
 
unsigned long long int Harsh(std::string key, unsigned long long int P)
{
    unsigned long long int result = (unsigned long long int)(key[0]);
    for (int i = 1; i < int(key.size()); i++)
        result = ((result * 37) + (unsigned long long int)(key[i]));
    return result;
}
 
void UpdatePos(int& pos, std::string* list, int P)
{
    int time = 0;
    if (list[pos] == "\0")
        return;
    while (time < P)
    {
        int origin = pos;
        int k = time + 1;
        if (k % 2 != 0)
        {
            pos += ((k + 1) / 2) * ((k + 1) / 2);
            pos = pos % P;
 
        }
        else
        {
            pos -= (k / 2) * (k / 2);
            pos = (pos % P + P) % P;
        }
        if (list[pos] == "\0")
            return;
        pos = origin;
        time++;
    }
    pos = -1;
}
 
int main()
{
    int N, P;
    std::cin >> N >> P;
    UpdateP(P);
 
    std::string* keys = new std::string[N];
    std::string* list = new std::string[P];
    int* keyposition = new int[N];
    for (int i = 0; i < N; i++)
    {
        std::cin >> keys[i];
        keyposition[i] = Harsh(keys[i], P) % P;
        UpdatePos(keyposition[i], list, P);
        if (keyposition[i] != -1)
            list[keyposition[i]] = keys[i];
    }
 
    for (int i = 0; i < N; i++)
    {
        if (keyposition[i] != -1)
            std::cout << keyposition[i] << ' ';
        else
            std::cout << '-' << ' ';
    }
    std::cout << std::endl;
    return 0;
}