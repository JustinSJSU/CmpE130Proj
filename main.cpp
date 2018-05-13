#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <ctype.h>

using namespace std;

class category{
public:
    int wordCount;
    vector<string> recommendations;
    vector<string> relatedWords;

    category();
    category(string words[], int length);
};

vector<string> parseSearch(string userSearch);
vector<string> erasedVector(vector<string> &parsedSearch, category* commonWords);
void adjustWordCount(vector<string> parsedSearch, vector<category*> list);
int totalCount(vector<category*> list1);
void printRecommendations(category* name);
void trainClassifier(category* name, vector<string> parsedSearch, string userSearch);
void resetWordCount(vector<category*> list);

int main() {

    string userSearch;
    int leftCount = 0;
    int rightCount = 0;
    vector<string> parsedSearch;
    vector<category*> list;
    vector<category*> L1, R1, LL2, LR2, RL2, RR2, LRL3, LRR3, RRL3, RRR3;

    string fillerWords[25] = {"a", "is", "what", "of", "are", "in", "there", "define", "go", "they", "how", "to", "can", "where", "that", "why", "meaning" };
    int fillerWordsLength = 17;

    string entertainmentWords[10] = {"television", "entertainment", "games", "movies", "shows", "theater", "tv", "videos", "music", "songs"};
    string technologyWords[10] = {"technology", "computer", "science", "electronics", "gadgets", "phone", "version", "engineer", "price", "latest"};
    string sportsWords[11] = {"sports", "football", "baseball", "soccer", "golf", "ball", "rules", "field", "injury", "penalty", "score"};
    string autosWords[10] = {"autos", "motorcycle", "vehicle", "cars", "automobile", "wheel", "engine", "model", "make", "price"};
    string politicsWords[10] = {"trump", "president", "united", "debate", "election", "political", "speech", "law", "bill", "states"};
    string moneyWords[10] = {"money", "currency", "coins", "convert", "usd", "exchange", "value", "stock", "bank", "price"};
    string lifestyleWords[10] = {"lifestyle", "home", "furniture", "family", "clothes", "fashion", "culture", "school", "luxury", "beauty"};
    string healthFitnessWords[10] = {"health", "fitness", "diet", "workout", "gym", "exercise", "outdoor", "trainer", "membership", "weight"};
    string foodWords[10] = {"food", "mcdonalds", "fast", "healthy", "sugar", "recipe", "restaurant", "kitchen", "fruit", "fat"};
    string weatherWords[10] = {"weather", "sunny", "rainy", "forecast", "temperature", "temp", "cloudy", "weekly", "tomorrow", "humidity"};

    category* commonWords = new category(fillerWords, 17);

    category* entertainment = new category(entertainmentWords, 10);
    list.push_back(entertainment);
    category* technology = new category(technologyWords, 10);
    list.push_back(technology);
    category* sports = new category(sportsWords, 11);
    list.push_back(sports);
    category* autos = new category(autosWords, 10);
    list.push_back(autos);
    category* politics = new category(politicsWords, 10);
    list.push_back(politics);
    category* money = new category(moneyWords, 10);
    list.push_back(money);
    category* lifestyle = new category(lifestyleWords, 10);
    list.push_back(lifestyle);
    category* healthFitness = new category(healthFitnessWords, 10);
    list.push_back(healthFitness);
    category* food = new category(foodWords, 10);
    list.push_back(food);
    category* weather = new category(weatherWords, 10);
    list.push_back(weather);

    //level 1 lists
    L1.push_back(entertainment);
    L1.push_back(technology);
    L1.push_back(sports);
    L1.push_back(autos);
    L1.push_back(money);
    R1.push_back(politics);
    R1.push_back(lifestyle);
    R1.push_back(healthFitness);
    R1.push_back(food);
    R1.push_back(weather);
    //level 2 lists
    LL2.push_back(sports);
    LL2.push_back(entertainment);
    LR2.push_back(technology);
    LR2.push_back(autos);
    LR2.push_back(money);
    RL2.push_back(politics);
    RL2.push_back(weather);
    RR2.push_back(lifestyle);
    RR2.push_back(healthFitness);
    RR2.push_back(food);
    //level 3 lists
    LRL3.push_back(technology);
    LRL3.push_back(money);
    RRL3.push_back(healthFitness);
    RRL3.push_back(food);


    while(1) {
        cout << "What would you like to search for?" << endl;
        getline(cin, userSearch);
        for (int i = 0; i < userSearch.length(); i++) {
            userSearch[i] = tolower(userSearch[i]);
        }
        parsedSearch = parseSearch(userSearch); //parsed string into words
        parsedSearch = erasedVector(parsedSearch, commonWords);
        adjustWordCount(parsedSearch, list);

        leftCount = totalCount(L1);
        rightCount = totalCount(R1);
        if (leftCount > rightCount) {

            leftCount = totalCount(LL2);
            rightCount = totalCount(LR2);
            if (leftCount > rightCount) {
                if (sports->wordCount > entertainment->wordCount) {

                    printRecommendations(sports);
                    trainClassifier(sports, parsedSearch, userSearch);
                } else {

                    printRecommendations(entertainment);
                    trainClassifier(entertainment, parsedSearch, userSearch);
                }

            } else {

                leftCount = totalCount(LRL3);
                rightCount = autos->wordCount;
                if (leftCount > rightCount) {

                    if (technology->wordCount > money->wordCount) {

                        printRecommendations(technology);
                        trainClassifier(technology, parsedSearch, userSearch);
                    } else {

                        printRecommendations(money);
                        trainClassifier(money, parsedSearch, userSearch);
                    }
                } else {
                    printRecommendations(autos);
                    trainClassifier(autos, parsedSearch, userSearch);
                }
            }
        } else {

            leftCount = totalCount(RL2);
            rightCount = totalCount(RR2);
            if (leftCount > rightCount) {

                if (politics->wordCount > weather->wordCount) {

                    printRecommendations(politics);
                    trainClassifier(politics, parsedSearch, userSearch);
                } else {

                    printRecommendations(weather);
                    trainClassifier(weather, parsedSearch, userSearch);
                }
            } else {

                leftCount = totalCount(RRL3);
                rightCount = lifestyle->wordCount;
                if (leftCount > rightCount) {

                    if (healthFitness->wordCount > food->wordCount) {

                        printRecommendations(healthFitness);
                        trainClassifier(healthFitness, parsedSearch, userSearch);
                    } else {
                        printRecommendations(food);
                        trainClassifier(food, parsedSearch, userSearch);
                    }
                } else {

                    printRecommendations(lifestyle);
                    trainClassifier(lifestyle, parsedSearch, userSearch);
                }
            }

        }

        cout << endl;
    }



    /*for(int i = 0; i < list.size(); i++){
        cout << list[i] <<" "<< list[i] -> wordCount<< endl;
    }
    for(int i = 0; i < parsedSearch.size(); i++){
        cout<< parsedSearch[i]<<endl;
    }*/



}

category::category(){ //default constructor
    wordCount = 0;
}

category::category(string words[], int length){ //places words into relatedWords array within class
    wordCount = 0;
    for(int a = 0; a < 5; a++){
        recommendations.push_back("initial recommendation");
    }
    for(int i = 0; i < length; i++){

        relatedWords.push_back(words[i]);

    }
}

vector<string> parseSearch(string userSearch){
    string temp;
    vector<string> parsed;
    for( int i = 0; i < userSearch.length(); i++ ){
        if(isalpha(userSearch[i])){

            //if character is a letter, add to temp variable
            temp += userSearch[i];
        }
        else if(isspace(userSearch[i])){

            //push back string to vector
            parsed.push_back(temp);
            //clear string
            temp = "";
        }
        else{
            parsed.push_back(temp);
            temp = "";
        }
    }
    parsed.push_back(temp);
    return parsed;
}

vector<string> erasedVector(vector<string> &parsedSearch, category* commonWords){
    for(int i = 0; i < commonWords -> relatedWords.size(); i++){
        for(int j = 0; j < parsedSearch.size(); j++){
            if(parsedSearch[j] == commonWords -> relatedWords[i]){
                parsedSearch.erase(parsedSearch.begin() + j);
            }
        }
    }
    return parsedSearch;
}

void adjustWordCount(vector<string> parsedSearch, vector<category*> list){
    for(int a = 0; a < parsedSearch.size(); a++){
        for(int b = 0; b < list.size(); b++){
            for(int c = 0; c < list[b] -> relatedWords.size(); c++){
                if(parsedSearch[a] == list[b] -> relatedWords[c]){
                    list[b] -> wordCount++;
                }
            }
        }
    }
}

int totalCount(vector<category*> list1){
    int list1Total = 0;
    for(int i = 0; i < list1.size(); i++){
        list1Total += list1[i] -> wordCount;
    }
    return list1Total;
}

void printRecommendations(category* name){

    cout<< "Recommendations: "<< endl;
    for(int i = 0; i < name -> recommendations.size(); i++){

        cout<< name -> recommendations[i]<< endl;
    }
    cout<<endl;
}

void trainClassifier(category* name, vector<string> parsedSearch, string userSearch){

    for(int i = 0; i < parsedSearch.size(); i++){
        name -> relatedWords.push_back(parsedSearch[i]);
    }
    name ->recommendations.push_back(userSearch);
    name ->recommendations.erase(name -> recommendations.begin());

}

void resetWordCount(vector<category*> list){

    for(int i = 0; i < list.size(); i++){

        list[i] -> wordCount = 0;
    }
}

