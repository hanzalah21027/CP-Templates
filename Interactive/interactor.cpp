struct Interactor{
    vector<int> arr;
    Interactor(){
        arr.resize(1000);
        for(int i = 0; i < 501; i++){
            arr[i] = 10;
        }
        for(int i = 501; i < 1000; i++){
            arr[i] = getRandomNumber(1, 9);
        }
    }
    bool query(int index){
        return arr[index] == 10;
    }
    void isValidOutput(int index){
        if(arr[index] == 10){
            cout << "Passed";
        }else{
            cout << "Failed";
        }
        cout << endl;
    }
};