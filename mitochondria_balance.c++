
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
using namespace std;
//こちらもデータファイルがあるのですが、著作権があり載せられません

int main(void){
    ifstream file("train_mitochondrion_cytoplasm_dataset.txt");
    if(!file){
        cerr << "1ファイルを開けませんでした。" << endl;
        exit(1);
    }

    string aa_order = "ACDEFGHIKLMNPQRSTVWY";
    map<char, int> aa_to_index;
    for(int i = 0; i < 20; i++){
        aa_to_index[aa_order[i]] = i;
    }

    int NUMBER_AMINO;
    file >> NUMBER_AMINO;
    vector<string> AMINO (NUMBER_AMINO);
    vector<double> status(NUMBER_AMINO,0.0);
    vector<vector<double>> aa_prob(NUMBER_AMINO, vector<double>(aa_order.size(),0.0));
    for(int i = 0; i < NUMBER_AMINO; i++){
        file >> AMINO[i];
        file >> status[i];
        for(int j = 0; j < AMINO[i].size(); j++){
            aa_prob[i][aa_to_index[AMINO[i][j]]] += 1/AMINO[i].size();
        }
    }
    file.close();

    ifstream file2("test_mitochondrion_cytoplasm_dataset.txt");
    if(!file2){
        cerr << "2ファイルを開けませんでした。" << endl;
        exit(1);
    }

    int NUMBER_AMINOS;
    file2 >> NUMBER_AMINOS;
    vector<vector<double>> aa_test(NUMBER_AMINOS, vector<double>(aa_order.size(),0.0));
    vector<int> statuss(NUMBER_AMINOS);
    vector<string> AMINOS (NUMBER_AMINOS);
    for(int i = 0; i < NUMBER_AMINOS; i++){
        file2 >> AMINOS[i];
        file2 >> statuss[i];
        for(int j = 0; j < AMINOS[i].size(); j++){
            aa_test[i][aa_to_index[AMINOS[i][j]]] += 1/AMINOS[i].size();
        }
    }
    file2.close();

    double probb;
    double min = 1e9;
    int min_id;
    vector<int> statusss(NUMBER_AMINOS);
    for(int i = 0; i < NUMBER_AMINOS; i++){
        min = 1;
        for(int k = 0; k < NUMBER_AMINO; k ++){
            for(int j = 0; j < 20; j++){
                probb += (aa_test[i][aa_to_index[AMINOS[i][j]]]-aa_prob[k][aa_to_index[AMINO[k][j]]])*(aa_test[i][aa_to_index[AMINOS[i][j]]]-aa_prob[k][aa_to_index[AMINO[k][j]]]);
            }
            if(min > probb){
            min = probb;
            min_id = k;
            }
            probb = 0;
        }
        statusss[i]=status[min_id];
    }
    double TP = 0;
    double FP = 0;
    double FN = 0;
    double TN = 0;
    for(int i = 0; i < NUMBER_AMINOS; i++){
        if(statusss[i]==statuss[i] && statusss[i]==1)TP++;
        if(statusss[i]==statuss[i] && statusss[i]==0)TN++;
        if(statusss[i]!=statuss[i] && statusss[i]==1)FP++;
        if(statusss[i]!=statuss[i] && statusss[i]==0)FN++;
    }
    double BA;
    BA = (TP/(TP+FN)+TN/(TN+FP))/2;
    cout << BA;

}
