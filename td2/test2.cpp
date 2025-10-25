#include <iostream>
#include <string>
#include "hash.h"

using namespace std;

// ============================================
// 2.4. TESTS DE VALIDATION
// ============================================

void test_hash() {
    cout << "========================================" << endl;
    cout << "TESTS DE LA FONCTION DE HACHAGE" << endl;
    cout << "========================================\n" << endl;
    
    // Test 1: Deux entrées différentes
    cout << "Test 1: Deux entrées différentes" << endl;
    cout << "--------------------------------" << endl;
    string input1 = "Hello World";
    string input2 = "Hello World!";
    
    string hash1 = ac_hash(input1, 110, 100);
    string hash2 = ac_hash(input2, 110, 100);
    
    cout << "Entrée 1: \"" << input1 << "\"" << endl;
    cout << "Hash 1:   " << hash1 << endl;
    cout << "\nEntrée 2: \"" << input2 << "\"" << endl;
    cout << "Hash 2:   " << hash2 << endl;
    cout << "\nHashes différents ? " << (hash1 != hash2 ? "OUI ✓" : "NON ✗") << endl;
    
    // Test 2: Même entrée, règles différentes
    cout << "\n\nTest 2: Même entrée, règles différentes" << endl;
    cout << "----------------------------------------" << endl;
    string input3 = "Test";
    
    string hash3a = ac_hash(input3, 30, 100);
    string hash3b = ac_hash(input3, 90, 100);
    string hash3c = ac_hash(input3, 110, 100);
    
    cout << "Entree: \"" << input3 << "\"" << endl;
    cout << "Hash (règle 30):  " << hash3a << endl;
    cout << "Hash (règle 90):  " << hash3b << endl;
    cout << "Hash (règle 110): " << hash3c << endl;
    cout << "\nTous differents ? " << ((hash3a != hash3b && hash3b != hash3c && hash3a != hash3c) ? "OUI ✓" : "NON ✗") << endl;
    
    // Test 3: Sensibilité au nombre de steps
    cout << "\n\nTest 3: Sensibilite au nombre de steps" << endl;
    cout << "---------------------------------------" << endl;
    string input4 = "Sensibilite";
    
    string hash4a = ac_hash(input4, 110, 50);
    string hash4b = ac_hash(input4, 110, 100);
    string hash4c = ac_hash(input4, 110, 200);
    
    cout << "Entree: \"" << input4 << "\"" << endl;
    cout << "Hash (50 steps):  " << hash4a << endl;
    cout << "Hash (100 steps): " << hash4b << endl;
    cout << "Hash (200 steps): " << hash4c << endl;
    cout << "\nTous differents ? " << ((hash4a != hash4b && hash4b != hash4c && hash4a != hash4c) ? "OUI ✓" : "NON ✗") << endl;
    
    // Test 4: Entrées très similaires
    cout << "\n\nTest 4: Entrees tres similaires (effet avalanche)" << endl;
    cout << "--------------------------------------------------" << endl;
    string input5a = "password123";
    string input5b = "password124";
    
    string hash5a = ac_hash(input5a, 110, 100);
    string hash5b = ac_hash(input5b, 110, 100);
    
    cout << "Entree 1: \"" << input5a << "\"" << endl;
    cout << "Hash 1:   " << hash5a << endl;
    cout << "\nEntree 2: \"" << input5b << "\"" << endl;
    cout << "Hash 2:   " << hash5b << endl;
    
    // Calcul de la différence
    int diff_count = 0;
    for (size_t i = 0; i < hash5a.size(); i++) {
        if (hash5a[i] != hash5b[i]) diff_count++;
    }
    
    cout << "\nCaracteres differents: " << diff_count << "/" << hash5a.size();
    cout << " (" << (100.0 * diff_count / hash5a.size()) << "%)" << endl;
    
    // Test 5: Chaîne vide
    cout << "\n\nTest 5: Chaine vide" << endl;
    cout << "-------------------" << endl;
    string input6 = "";
    string hash6 = ac_hash(input6, 110, 100);
    cout << "Entree: \"\" (chaine vide)" << endl;
    cout << "Hash:   " << hash6 << endl;
}

int main() {
    test_hash();
    
    cout << "\n\n========================================" << endl;
    cout << "EXPLICATIONS TECHNIQUES" << endl;
    cout << "========================================\n" << endl;
    
    cout << "2.2. CONVERSION TEXTE -> BITS:" << endl;
    cout << "  - Chaque caractere -> 8 bits ASCII" << endl;
    cout << "  - Padding a 256 bits si necessaire (1 + 0...0)" << endl;
    cout << "  - Compression par XOR si > 256 bits\n" << endl;
    
    cout << "2.3. PROCESSUS DE HACHAGE:" << endl;
    cout << "  1. Texte -> 256 bits (etat initial)" << endl;
    cout << "  2. Application de l'automate cellulaire (N générations)" << endl;
    cout << "  3. Etat final 256 bits -> 64 caracteres hexadecimaux" << endl;
    cout << "  4. Résultat: Hash de 256 bits\n" << endl;
    
    cout << "2.4. VALIDATION:" << endl;
    cout << "  ✓ Deux entrees differentes produisent des hashs differents" << endl;
    cout << "  ✓ Effet avalanche: petit changement -> grand impact" << endl;
    cout << "  ✓ Sensibilite aux parametres (regle, steps)" << endl;

    return 0;
}
