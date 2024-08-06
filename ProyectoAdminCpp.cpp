// ProyectoAdminCpp.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip> // Para std::setw y std::fixed
#include <ctime>   // Para funciones de fecha y hora
#include <sstream> // Para conversión de fechas

using namespace std;

// Función para calcular la diferencia en días entre dos fechas
int calculateDaysDifference(const string& startDateStr, const string& endDateStr) {
    struct tm startDate = {}, endDate = {};
    istringstream(startDateStr) >> get_time(&startDate, "%Y-%m-%d");
    istringstream(endDateStr) >> get_time(&endDate, "%Y-%m-%d");

    time_t start = mktime(&startDate);
    time_t end = mktime(&endDate);
    double seconds = difftime(end, start);
    int days = seconds / (60 * 60 * 24);

    return days;
}

// Clase que representa un Proyecto
class Project {
public:
    string name;
    string description;
    int hours; // Horas/Hombre estimadas
    string startDate;
    string endDate;
    double hourlyRate; // Tarifa H/H

    Project(string name, string description, int hours, string startDate, string endDate, double hourlyRate)
        : name(name), description(description), hours(hours), startDate(startDate), endDate(endDate), hourlyRate(hourlyRate) {}

    // Método para calcular el valor del proyecto
    double calculateValue() const {
        int totalDays = calculateDaysDifference(startDate, endDate);
        int totalHours = totalDays * 8; // Suponiendo 8 horas de trabajo por día
        return totalHours * hourlyRate;
    }

    // Método para mostrar la información del proyecto
    void display() const {
        cout << "Nombre: " << name << endl;
        cout << "Descripción: " << description << endl;
        cout << "Horas/Hombre: " << hours << endl;
        cout << "Fecha de Inicio: " << startDate << endl;
        cout << "Fecha Final: " << endDate << endl;
        cout << "Tarifa H/H: $" << fixed << setprecision(2) << hourlyRate << endl;
        cout << "Horas/Hombre Total: " << calculateDaysDifference(startDate, endDate) * 8 << endl;
        cout << "Valor del Proyecto: $" << fixed << setprecision(2) << calculateValue() << endl;
    }
};

// Clase que maneja los proyectos
class ProjectManager {
private:
    vector<Project> projects;
    const string filename = "projects.txt";

    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) return;

        string name, description, startDate, endDate;
        int hours;
        double hourlyRate;

        while (getline(file, name) && getline(file, description) && file >> hours >> ws &&
            getline(file, startDate) && getline(file, endDate) && file >> hourlyRate >> ws) {
            projects.emplace_back(name, description, hours, startDate, endDate, hourlyRate);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) return;

        for (const auto& project : projects) {
            file << project.name << endl;
            file << project.description << endl;
            file << project.hours << endl;
            file << project.startDate << endl;
            file << project.endDate << endl;
            file << project.hourlyRate << endl;
        }
        file.close();
    }

public:
    ProjectManager() {
        loadFromFile();
    }

    ~ProjectManager() {
        saveToFile();
    }

    void addProject(const string& name, const string& description, int hours, const string& startDate, const string& endDate, double hourlyRate) {
        projects.emplace_back(name, description, hours, startDate, endDate, hourlyRate);
    }

    void listProjects() const {
        if (projects.empty()) {
            cout << "No hay proyectos disponibles." << endl;
            return;
        }

        for (const auto& project : projects) {
            project.display();
            cout << "------------------------" << endl;
        }
    }

    void deleteProject(const string& name) {
        auto it = remove_if(projects.begin(), projects.end(), [&](const Project& project) {
            return project.name == name;
            });

        if (it != projects.end()) {
            projects.erase(it, projects.end());
            cout << "Proyecto eliminado." << endl;
        }
        else {
            cout << "Proyecto no encontrado." << endl;
        }
    }
};

int main() {
    ProjectManager pm;
    int choice;
    string name, description, startDate, endDate;
    int hours;
    double hourlyRate;

    while (true) {
        cout << "Gestor de Proyectos\n";
        cout << "1. Crear Proyecto\n";
        cout << "2. Listar Proyectos\n";
        cout << "3. Eliminar Proyecto\n";
        cout << "4. Salir\n";
        cout << "Elija una opción: ";
        cin >> choice;
        cin.ignore(); // Limpiar el buffer de entrada

        switch (choice) {
        case 1:
            cout << "Ingrese el nombre del proyecto: ";
            getline(cin, name);
            cout << "Ingrese la descripción del proyecto: ";
            getline(cin, description);
            cout << "Ingrese las horas/hombre estimadas: ";
            cin >> hours;
            cin.ignore(); // Limpiar el buffer de entrada
            cout << "Ingrese la fecha de inicio (formato YYYY-MM-DD): ";
            getline(cin, startDate);
            cout << "Ingrese la fecha final (formato YYYY-MM-DD): ";
            getline(cin, endDate);
            cout << "Ingrese la tarifa por hora-hombre: $";
            cin >> hourlyRate;
            cin.ignore(); // Limpiar el buffer de entrada
            pm.addProject(name, description, hours, startDate, endDate, hourlyRate);
            break;
        case 2:
            pm.listProjects();
            break;
        case 3:
            cout << "Ingrese el nombre del proyecto a eliminar: ";
            getline(cin, name);
            pm.deleteProject(name);
            break;
        case 4:
            return 0;
        default:
            cout << "Opción no válida." << endl;
        }
    }
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
