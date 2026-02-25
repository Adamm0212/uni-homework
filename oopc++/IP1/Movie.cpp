#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

class Movie {
    // private by default
    private:
        static int counter;
        static int id;

        string name;
        int year;
        double rating;
        int uniqueId;
    public:
        Movie(string name, int year, double rating) {
            setName(name);
            setYear(year);
            setRating(rating);
            uniqueId = id;
            id++; counter++;
        }

        Movie(string name, int year) {
            setName(name);
            setYear(year);
            rating = 0.0;
            uniqueId = id;
            id++; counter++;
        }

        ~Movie() {
            counter--;
        }
        
        string toString() {
            stringstream ss;
            ss << name << " - " << year << " (" << rating << ")"; 
            return ss.str();
        }

        void setName(string name) {
            this->name = name;
        }

        void setYear(int year) {
            this->year = year;
        }

        void setRating(double rating) {
            if (rating >= 0.0 && rating <= 10.0) {
                this->rating = rating;
            } else {
                throw invalid_argument("Rating has to be between 0 and 10");
            }
        }
        
        string getName() {
            return name;
        }

        int getYear() {
            return year;
        }

        double getRating() {
            return rating;
        }
};

int Movie::counter = 0;
int Movie::id = 1;

int main (int argv, char* argc[]) {
    
    return 0;
}