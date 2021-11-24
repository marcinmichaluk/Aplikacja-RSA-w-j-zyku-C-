#pragma once
#ifndef RSA_H
#define RSA_H

#include<vector>
#include<string>
#include<math.h>
#include<iostream>
#include<time.h>
#include<fstream>
#include<cstdlib>


class RSA {
public:
    RSA();
    int get_private_key();
    std::vector<int> get_public_keys();
    std::vector<long int> encrypt(std::string string);
    void decrypt();
    void clear_file(std::string);
    int get_p();
    int get_q();
    int get_n();
    int get_e();
    int get_d();
    int get_phi_n();
    void write_in_file();
    void set_private_key();
    void set_public_key();
    void set_mod();

private:
    void generate_keys();
    int generate_private_key();
    bool isprime(int n);
    int totient(int n);
    int generate_prime();
    int generate_random(int from = 2, int to = pow(2, 10));
    int generate_e();
    int gcd(int x, int y);
    int mod(int x, int y);
    int ord(char c);
    char chr(int i);
    int pow_mod(int p, int q, int n);

    int p, q, n, phi_n, e, d;
};


#endif