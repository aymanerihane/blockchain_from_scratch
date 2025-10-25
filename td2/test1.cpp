#include <iostream>
#include <vector>
#include "automate_cellulaire.h"
using namespace std;

// 1.3. Fonction de test
void test_rule(int rule_num, const vector<int>& initial_state, int generations) {
    CellularAutomaton ca(rule_num);
    
    cout << "\n===== Test de la Règle " << rule_num << " =====" << endl;
    ca.print_rule();
    cout << "\nÉtat initial: ";
    
    ca.init_state(initial_state);
    ca.print_state_binary();
    ca.print_state();
    
    cout << "\nÉvolution:" << endl;
    for (int gen = 1; gen <= generations; gen++) {
        ca.evolve();
        cout << "Gen " << gen << ": ";
        ca.print_state_binary();
        ca.print_state();
    }
}

int main() {
    // Test 1: Règle 110 avec état initial 1001010
    cout << "========================================" << endl;
    cout << "Test 1: Règle 110" << endl;
    cout << "========================================" << endl;
    vector<int> state1 = {1, 0, 0, 1, 0, 1, 0};
    test_rule(110, state1, 5);
    
    // Test 2: Règle 30 (comportement chaotique)
    cout << "\n========================================" << endl;
    cout << "Test 2: Règle 30" << endl;
    cout << "========================================" << endl;
    vector<int> state2 = {0, 0, 0, 1, 0, 0, 0};
    test_rule(30, state2, 5);
    
    // Test 3: Règle 90 (triangle de Sierpinski)
    cout << "\n========================================" << endl;
    cout << "Test 3: Règle 90" << endl;
    cout << "========================================" << endl;
    vector<int> state3 = {0, 0, 0, 1, 0, 0, 0};
    test_rule(90, state3, 5);
    
    // Test 4: État initial plus grand pour la Règle 110
    cout << "\n========================================" << endl;
    cout << "Test 4: Règle 110 - État plus large" << endl;
    cout << "========================================" << endl;
    vector<int> state4(21, 0);
    state4[10] = 1; // Une seule cellule au centre
    test_rule(110, state4, 10);
    
    return 0;
}
