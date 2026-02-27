#include <iostream>
#include <stdexcept>
#include <sstream>

#include <cassert>
#include <vector>

using namespace std;

class Movie {

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
        ss << name << " - " << year << " (" << rating << ") " << "ID = " << uniqueId; 
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

    int getID() {
        return uniqueId;
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

    static int getCount() {
        return counter;
    }
};

int Movie::counter = 0;
int Movie::id = 1;

int main (int argv, char* argc[]) {
    try {
        // test 1
    {
        Movie m1("Inception", 2010, 8.8);

        assert(m1.getName() == "Inception");
        assert(m1.getYear() == 2010);
        assert(m1.getRating() == 8.8);
        assert(m1.getID() == 1);

        string expected = "Inception - 2010 (8.8) ID = 1";
        assert(m1.toString() == expected);

        assert(Movie::getCount() == 1);

        // test 2
        m1.setName("Interstellar");
        m1.setYear(2014);
        m1.setRating(9.5);

        assert(m1.getName() == "Interstellar");
        assert(m1.getYear() == 2014);
        assert(m1.getRating() == 9.5);
        
        // test 3
        bool exception = false;

        try {
            m1.setRating(25.0);
        } catch (invalid_argument& e) {
            exception = true;
            cout << "FAKE Error: " << e.what() << "\n";
        }
        assert(exception);
    }
        // test 4   
    {
        Movie m2("Matrix", 1999, 9.0);
        Movie m3("Avatar", 2009);

        assert(m2.getID() == 2);
        assert(m3.getID() == 3);

        assert(m2.getID() < m3.getID());
        assert(Movie::getCount() == 2);

        Movie* m4 = new Movie("Whiplash", 2014, 8.5);
        assert(m4->getID() == 4);
        delete m4;

        m4 = new Movie("Eyes Wide Shut", 1999, 7.5);
        assert(m4->getID() == 5);
        delete m4;
    }
        // test 5
        vector<Movie*> movies;

        assert(Movie::getCount() == 0);

        movies.push_back(new Movie("Movie1", 2000, 5.0));
        assert(Movie::getCount() == 1);

        movies.push_back(new Movie("Movie2", 2001, 6.0));
        assert(Movie::getCount() == 2);

        movies.push_back(new Movie("Movie3", 2002, 7.0));
        assert(Movie::getCount() == 3);

        for (Movie* m : movies) {
            delete m;
        }

        movies.clear();

        assert(Movie::getCount() == 0); 

    }
    catch (...) {
        assert(false);
    }
    cout << "All tests were correct\n";
    return 0;
}
