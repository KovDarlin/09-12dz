#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Company;

class Department {
private:
    std::string name;
    std::weak_ptr<Company> company;
public:
    Department(const std::string& name) : name(name) {}
    void setCompany(std::shared_ptr<Company> comp) {
        company = comp;
    }

    void display() const; 
};

class Company : public std::enable_shared_from_this<Company> {
private:
    std::string name;
    std::vector<std::shared_ptr<Department>> departments;

public:
    Company(const std::string& name) : name(name) {}

    void addDepartment(const std::shared_ptr<Department>& dept) {
        departments.push_back(dept);
        dept->setCompany(shared_from_this());
    }

    std::string getName() const {
        return name;
    }

    void displayDepartments() const {
        std::cout << "Company: " << name << " has departments:\n";
        for (const auto& dept : departments) {
            dept->display();
        }
    }
};

void Department::display() const {
    std::cout << "Department: " << name;
    if (auto compPtr = company.lock()) {
        std::cout << " (Company: " << compPtr->getName() << ")";
    }
    else {
        std::cout << " (Company: [expired])";
    }
    std::cout << std::endl;
}

int main() {
    std::shared_ptr<Company> company = std::make_shared<Company>("ITdev");

    auto dev = std::make_shared<Department>("Development");
    auto designer = std::make_shared<Department>("Designer");
    auto admin = std::make_shared<Department>("Administrator");
    auto manager = std::make_shared<Department>("Manager");

    company->addDepartment(dev);
    company->addDepartment(designer);
    company->addDepartment(admin);
    company->addDepartment(manager);
    company->displayDepartments();
}
