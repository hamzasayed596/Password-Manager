#include <bits/stdc++.h>
#define all(v) (v).begin(), (v).end()
using namespace std;
namespace fs = std::filesystem;
typedef long double ld;
typedef long long ll; typedef unsigned long long ull;

void sign_up();
void sign_in();

void waiting_points (ll pn, ll ms) {
    while (pn--) {
        this_thread::sleep_for(chrono::milliseconds(ms));
        cout << ".";
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
}

void encrypt(string &s) {
    if (s.empty()) {
        return;
    }
    s[0] = static_cast<char>(static_cast<ll>(s[0])+static_cast<ll>(pow((3*2),sqrt(3+2)/2)) % 128);
    for (ll i = 1; i < s.length(); i++) {
        s[i] =static_cast<char>(static_cast<ll>(s[i])+(static_cast<ll>(pow((i*2),sqrt(i+2)/2)) % 128));
    }
}

void decrypt(string &s) {
    if (s.empty()) {
        return;
    }
    s[0] = static_cast<char>(static_cast<ll>(s[0])-static_cast<ll>(pow((3*2),sqrt(3+2)/2)) % 128);
    for (ll i = 1; i < s.length(); i++) {
        s[i] =static_cast<char>(static_cast<ll>(s[i])-(static_cast<ll>(pow((i*2),sqrt(i+2)/2)) % 128));
    }
}

void add_password(string &username) {
    cout << "Please input the name of the platform" << endl;
    string name;
    cin >> name;
    cout << "Please input the user name or the email (the thing you use in signing in)" << endl;
    string email;
    cin >> email;
    cout << "Please input the password" << endl;
    string password;
    cin >> password;
    encrypt(password);
    ofstream file(username, ios_base::app);
    file << name << ": " << email << " --> " << password << endl;
    file.close();
    cout << "Do you wanna add another password?\ninput y or n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        add_password(username);
    }
    else {
        cout << "Thanks for trusting us\nYou can exit!" << endl;
    }
}

void get_password(string &username) {
    cout << "Please input the name of the platform" << endl;
    string name;
    cin >> name;
    ifstream file(username);
    string l;
    bool d = false;
    string line;
    while (getline(file, l)) {
        if (l.find(name) != string::npos && l.find(": ") != string::npos && l.find(" --> ") != string::npos) {
            cout << "Collecting data";
            waiting_points(5,500);
            cout << endl;
            line = l;
            d = true;
            break;
        }
    }
    if (d) {
        string platform;
        string email;
        string password;
        ll i = 0;
        while (i < line.size() && line[i] != ':') {
            platform += line[i];
            i++;
        }
        i+=2;
        while (i < line.size() && line[i] != ' ') {
            email += line[i];
            i++;
        }
        i+=5;
        while (i < line.size()) {
            password += line[i];
            i++;
        }
        decrypt(password);
        cout << "Platform: " << platform << " || Email: " << email << " || Password: " << password << endl;
    }
    else {
        cout << "Sorry but we couldn't find any data related to this platform you may spelled it wrongly!\nHowever you can try again:|" << endl;
        get_password(username);
    }
}

void suggest_password(string &suggest) {
    ll limit;
    cout << "Please input the number of characters" << endl;
    cin >> limit;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<ll> dis;
    suggest.clear();
    while (limit) {
        if (limit) {
            dis = uniform_int_distribution<ll>(65,90);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
        if (limit) {
            dis = uniform_int_distribution<ll> (33,47);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
        if (limit) {
            dis = uniform_int_distribution<ll> (48,57);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
        if (limit) {
            dis = uniform_int_distribution<ll> (97,122);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
        if (limit) {
            dis = uniform_int_distribution<ll> (58,64);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
        if (limit) {
            dis = uniform_int_distribution<ll> (123,128);
            suggest += static_cast<char>(dis(gen));
            limit--;
        }
    }
    shuffle(suggest.begin(), suggest.end(), gen);
    cout << suggest << endl;
    cout << "Do you want another suggestion?\ninput y or n" << endl;
    char answer;
    cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        suggest_password(suggest);
    }
    else {
        cout << "Thanks for trusting us\nYou can exit!" << endl;
    }
}

void sign_up() {
    cout << "Signing up";
    waiting_points(3, 750);
    cout << endl;
    cout << "Enter username: " << endl;
    string username;
    cin >> username;
    if (fs::exists(username)) {
        cout << "Username already exists\nRedirecting to sign in page";
        waiting_points(5, 500);
        cout << endl;
        sign_in();
    }
    cout << "Enter password: " << endl;
    string password;
    cin >> password;
    encrypt(password);
    ofstream file(username, ios_base::app);
    file << password << endl;
    file.close();
    cout << "Welcome " << username << "!" << endl;
    cout << "Do you want to add a password or get or suggest one?\ninput (a or g or s) please:" << endl;
    char input;
    while (cin >> input) {
        if (input == 'a' || input == 'A') {
            add_password(username);
        }
        else if (input == 'g' || input == 'G') {
            get_password(username);
        }
        else if (input == 's' || input == 'S') {
            string suggest;
            suggest_password(suggest);
        }
        else {
            cout << "Please enter a valid option!" << endl;
            cin.clear();
        }
    }
}

void sign_in() {
    cout << "Waiting";
    waiting_points(3, 750);
    cout << endl;
    cout << "Enter username: " << endl;
    string username;
    cin >> username;
    //username += ".txt";
    if (fs::exists(username)) {
        cout << "Enter password: " << endl;
        string password;
        while (cin >> password) {
            ifstream file(username);
            cout << "Signing in";
            waiting_points(5, 500);
            cout << endl;
            string line;
            getline(file, line);
            decrypt(line);
            if (line == password) {
                file.close();
                cout << "Welcome back " << username << "!" << endl;
                cout << "Do you want to add a password or get or suggest one?\ninput (a or g or s) please:" << endl;
                char input;
                while (cin >> input) {
                    if (input == 'a' || input == 'A') {
                        add_password(username);
                    }
                    else if (input == 'g' || input == 'G') {
                        get_password(username);
                    }
                    else if (input == 's' || input == 'S') {
                        string suggest;
                        suggest_password(suggest);
                    }
                    else {
                        cout << "Please enter a valid option!" << endl;
                        cin.clear();
                    }
                }
            }
            else {
                cout << "Your password is incorrect.\nPlease enter again" << endl;
                cin.clear();
                file.close();
            }
        }
    }
    else {
        cout << "Can't find a user with this name ):\nRedirecting to sign up page";
        waiting_points(5, 500);
        cout << endl;
        sign_up();
    }
}

signed main() {
    cout << "Sign in/up (input i or u)" << endl;
    char input;
    while (cin >> input) {
        if (input == 'i') {
            sign_in();
        }
        else if (input == 'u') {
            sign_up();
        }
        else {
            cout << "Please enter a valid option!" << endl;
            cin.clear();
        }
    }
}
