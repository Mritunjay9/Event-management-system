#include <iostream>
#include <fstream>
using namespace std;

class EventBase {
protected:
    string name;
    string date;
    int currentCount;
    string attendeeNames[100];
    string attendeeEmails[100];

public:
    static int totalRegistrations;


    EventBase(string n, string d) {
        name = n;
        date = d;
        currentCount = 0;
    }



    ~EventBase() {
        cout << "Destructor called for event: " << name << endl;

    }


    void registerAttendee() {
        if (currentCount >= 100) {
            cout << "Event attendee limit reached!\n";
            return;
        }

        cout << "Enter your name: ";
        cin >> ws;
        getline(cin, attendeeNames[currentCount]);
        cout << "Enter your email: ";
        getline(cin, attendeeEmails[currentCount]);



        ofstream outFile("C:\\Users\\mritu\\OneDrive\\Desktop\\attendees.txt",ios::app);
        if (outFile.is_open()) {
            outFile << "Event: " << name << " (" << date << ")\n";
            outFile << "Name: " << attendeeNames[currentCount] << ", Email: " << attendeeEmails[currentCount] << "\n";

            outFile.close();
        }

        currentCount++;
        totalRegistrations++;

        cout << "Registration successful! Total for this event: " << currentCount << "\n";
    }



    void showAttendees() {
        cout << "\nAttendees for " << name << " (" << date << "):\n";
        for (int i = 0; i < currentCount; i++) {

            cout << i + 1 << ". " << attendeeNames[i] << " (" << attendeeEmails[i] << ")\n";
        }
        cout << "Total attendees: " << currentCount << "\n";
    }



    static void showAttendeeFromFile() {
        ifstream inFile("C:\\Users\\mritu\\OneDrive\\Desktop\\attendees.txt");

        if (!inFile) {
            cout << "Unable to open the file for reading.\n";
            return;
        }

        string line;
        cout << "\nDisplaying all attendees from the file:\n";

        while (getline(inFile, line)) {
            cout << line << endl;
        }

        inFile.close();
    }

    friend void venue_avail(const EventBase& e);
};


int EventBase::totalRegistrations = 0;


void venue_avail(const EventBase& e) {
    if (e.currentCount > 10) {
        cout << "Venue is available" << endl;
    } else {
        cout << "Venue is not available" << endl;
    }
}


class Event : public EventBase {
public:
    Event(string n, string d) : EventBase(n, d) {}

};

int main() {

    Event pythonWorkshop("Python Workshop", "27-10-2025");
    Event aiBootcamp("AI Bootcamp", "15-11-2025");

    while (true) {
        cout << "\nEvent Management System";
        cout << "\n1. Register for Python Workshop";
        cout << "\n2. Register for AI Bootcamp";
        cout << "\n3. View attendees (Python Workshop)";
        cout << "\n4. View attendees (AI Bootcamp)";
        cout << "\n5. View total registrations (all events)";
        cout << "\n6. Venue for (Python)";
        cout << "\n7. Venue for (AI)";
        cout << "\n8. Show Attendee From File";
        cout << "\n9. Exit";
        cout << "\nChoose option: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                pythonWorkshop.registerAttendee();
                break;
            case 2:
                aiBootcamp.registerAttendee();
                break;
            case 3:
                pythonWorkshop.showAttendees();
                break;
            case 4:
                aiBootcamp.showAttendees();
                break;
            case 5:
                cout << "Total registrations across all events: " << EventBase::totalRegistrations << "\n";
                break;
            case 6:
                venue_avail(pythonWorkshop);
                break;
            case 7:
                venue_avail(aiBootcamp);
                break;
            case 8:
                EventBase::showAttendeeFromFile();
                break;
            case 9:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
