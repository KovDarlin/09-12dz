#include <iostream>
#include <string>
#include <vector>

#include <memory>


class Employee {
private:
	int id;
	std::string name;
public:
	Employee(const std::string& name, int id) : name(name), id(id) {}
	void display() const {
		std::cout << "ID employee: " << id << " - name: " << name << std::endl;
	}
};

void transfer(std::unique_ptr<Employee>&& emp, std::vector<std::unique_ptr<Employee>>& destList) {
	destList.push_back(std::move(emp));
}


int main() {
	std::vector<std::unique_ptr<Employee>> list1;
	std::vector<std::unique_ptr<Employee>> list2;

	list1.push_back(std::make_unique<Employee>("Kovalenko Darlin", 1));
	list1.push_back(std::make_unique<Employee>("Stepanchuk Nona", 2));
	list1.push_back(std::make_unique<Employee>("Gruch Marina", 3));

	transfer(std::move(list1[1]), list2);
	list1[1] = nullptr;


	std::cout << "\nList 1:\n";
	for (const auto& emp : list1) {
		if (emp) emp->display();
		else std::cout << "[transfer to list2]\n";
	}

	std::cout << "\nList 2:\n";
	for (const auto& emp : list2) {
		emp->display();
	}
}
