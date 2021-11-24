#include "RSA.h"

/***** Konstruktor *****/
RSA::RSA() {
    srand(static_cast <unsigned> (time(0)));
    generate_keys();
}


/***** Metody *****/
void RSA::set_mod() {
    int mod;
    std::cout << "Wprowadz modul: " << std::endl;
    std::cin >> mod;
    this->n = mod;
}
void RSA::set_private_key() {
    int key;
    std::cout << "Wprowadz klucz prywatny:" << std::endl;
    std::cin >> key;
    this->d = key;
}
void RSA::set_public_key() {
    int key;
    std::cout << "Podaj klucz publiczny." << std::endl;
    std::cin >> key;
    this->e = key;
}
int RSA::get_p() {
    return this->p;
}

int RSA::get_q() {
    return this->q;
}

int RSA::get_n() {
    return this->n;
}

int RSA::get_e() {
    return this->e;
}

int RSA::get_d() {
    return this->d;
}

int RSA::get_phi_n() {
    return this->phi_n;
}

int RSA::get_private_key() {
    return this->d;
}


std::vector<int> RSA::get_public_keys() {
    std::vector<int> vec;
    vec.push_back(this->n);
    vec.push_back(this->e);
    return vec;
}
int RSA::pow_mod(int p, int q,int n) { 
    int result = p;
    if (gcd(p, n) == 1)
        q = q % phi_n;
    for (int i = 1; i < q; i++)
        result = (result * p) % n;
    return result;
}

std::vector<long int> RSA::encrypt(std::string string) {
    std::vector<long int> ret;
    std::fstream file;
    file.open("cryptogram.txt", std::ios::app);
    for (int i = 0; i < string.length();i++) {
        int ascii = ord(string.at(i));
        long long int encripted = pow_mod(ascii, this->e,this->n);
        ret.push_back(encripted);
        file << encripted << std::endl;
        std::cout << string.at(i) << " " << encripted << std::endl;
    }
    file.close();
    return ret;
}
std::vector<long int> RSA::decrypt()
{
    std::vector<long int> ret;
    std::string line;
    int cryptogram;
    char letter;
    std::string txt;
    std::fstream file;
    file.open("cryptogram.txt", std::ios::in);
    if (file.good() == false)
    {
        std::cout << "Nie udalo sie otworzyc pliku :(";
        exit(0);
    }
    while (getline(file, line))
    {
       
          cryptogram = atoi(line.c_str());
          int decrypted = pow_mod(cryptogram, this->d, this->n);
          letter = (char)decrypted;
          ret.push_back(decrypted);
          std::cout << letter;
    }
    file.close();
}

void RSA::generate_keys() {
    this->p = generate_prime();
    this->q = generate_prime();
    this->n = p * q;
    int y = totient(p);
    int x = totient(q);
    this->phi_n = x * y;
    this->e = generate_e();
    this->d = generate_private_key();
}


int RSA::totient(int n) {
    if (isprime(n)) {
        return n - 1;
    }
}
bool RSA::isprime(int n) {
    if (n <= 1)  return false;
    if (n <= 3)  return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;

    return true;
}


int RSA::generate_e() {
    while (true) {
        int generated = this->generate_random(2, phi_n);
        if (this->gcd(this->phi_n, generated) == 1) {
            return generated;
        }
    }
}

int RSA::gcd(int x, int y) {
    int rest = 1;
    while (y != 0) {
        rest = x % y;
        x = y;
        y = rest;
    }
    return x;
}


int RSA::ord(char c) {
    return (int)c;
}


char RSA::chr(int i) {
    return (char)i;
}


int RSA::generate_prime() {
    int e;
    do {
        e = generate_random(0,500);
    } while (!isprime(e));
    return e;
}

int RSA::generate_random(int from, int to) {
    return from + (rand() % to);
}

int RSA::mod(int x, int y) {
    if (x < y) {
        return x;
    }
    return x % y;
}

int RSA::generate_private_key() {
    int d = 1;
    while (mod(d * this->e, this->phi_n) != 1) {
        d++;
    }
    return d;
}
void RSA::write_in_file() {
    std::fstream file;
    file.open("parameters.txt", std::ios::app);
    file << "Parametry: " << std::endl << "Pierwsza liczba pierwsza (p) :" << this->p << std::endl << "Druga liczba peirwsza (q) : " << this->q << std::endl;
    file << "Iloczyn p i q :" << this->n << std::endl << "Funkcja phi dla n : " << this->phi_n << std::endl << "Liczba E do klucza publicznego : " << this->e << std::endl;
    file << "Liczba D do klucza prywatnego : " << this->d << std::endl;
}

void parameters(RSA x) {
    std::cout << "Parametry : " << std::endl << "Pierwsza liczba pierwsza (p) : " << x.get_p() << std::endl << "Druga liczba pierwsza (q) : " << x.get_q() << std::endl;
    std::cout << "Iloczyn p i q : " << x.get_n() << std::endl << "Funkcja phi dla n : " << x.get_phi_n() << std::endl << "Liczba E do klucza publicznego : " << x.get_e() << std::endl;
    std::cout << "Liczba D do klucza prywatnego : " << x.get_d() << std::endl;
}

int menu() {
    int input = 0;
    std::cout << "\n" << "     " << "Mozliwe operacje : " << std::endl << std::endl;
    std::cout << "     " << "1.Generuj klucze" << std::endl;
    std::cout << "     " << "2.Wyswietlenie klucza prywatnego" << std::endl;
    std::cout << "     " << "3.Wyswietl parametry" << std::endl;
    std::cout << "     " << "4.Zapisz parametry do pliku:" << std::endl;
    std::cout << "     " << "5.Wpisz tekst jawny (Szyfrowanie)" << std::endl;
    std::cout << "     " << "6.Wpisz tekst zaszyfrowany (Deszyfrowanie)" << std::endl; //deszyfrowanie trzeba napisac
    std::cout << "     " << "7.Exit" << std::endl;
    std::cout << "\n" << "     " << "Operacja ktora chcesz wykonac to : ";

    std::cin >> input;
    std::cout << std::endl;

    return input;
}

/***** MAIN *****/
int main() {
    RSA x;

    std::string txt;

    while (true) {
        int input = 0;
        input = menu();
        switch (input) {

        case 1:
            std::cout << "Wygenerowano klucze " << std::endl;
            break;

        case 2:
            std::cout << "Twoj klucz prywatny: " << x.get_private_key() << std::endl;
            break;

        case 3:
            parameters(x);
            break;

        case 4:
            std::cout << "Zapisano parametry do pliku" << std::endl;
            x.write_in_file();
            break;

        case 5:
            std::cout << "Podaj teskt do zaszyfrowania: ";
            std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');
            getline(std::cin, txt);
            x.encrypt(txt);
            break;

        case 6:
            x.decrypt();
            break;

        case 7:
            std::string message;
            return 0;
        case 8:
            std::cout << "Ustawianie parametrow wprowadzonych przez uzytkownika: " << std::endl;
            x.set_mod();
            x.set_private_key();
            x.set_public_key();
            break;
        default:
            std::cout << "\n     Prosze podac poprawny numer operacji\n";
        }
    
    }
}