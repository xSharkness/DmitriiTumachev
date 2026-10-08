#include <iostream>
#include <string>
#include <vector>

namespace problem {
  void problem1() {
    int number = 0;
    int result = 1;
    std::cin >> number;
    if ((9999 < number) and (number < 100000)) {
      for (int i = 0; i < 5; i++) {
        result = result * (number % 10);
        number = number / 10;
      }
      std::cout << result << "\n";
    }
  }

  void problem2() {
    int number = 0;
    int even_result = 0;
    int odd_result = 0;
    std::cin >> number;
    if ((99999 < number) and (number < 1000000)) {
      for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
          even_result = even_result + (number % 10);
        }
        else {
          odd_result = odd_result + (number % 10);
        }
        number = number / 10;
      }
      std::cout << odd_result << even_result << "\n";
    }
  }

  void problem3() {
    int N = 0;
    float sum = 0;
    int count = 0;
    int number = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
      std::cin >> number;
      if (number % 3 == 0) {
        sum = sum + number;
        count = count + 1;
      }
    }
    if (count != 0) {
      std::cout << sum / N << "\n";
    }
    else {
      std::cout << -1 << "\n";
    }
  }
  
  void problem4() {
    int first = 1;
    int second = 1;
    int next = 0;
    int count = 3;
    int A = 0;
    std::cin >> A;
    if (A > 1) {
      while (first + second < A) {
        next = first + second;
        first = second;
        second = next;
        count += 1;
        }
      if (first + second == A) {
          std::cout << count << "\n";
        }
      else {
        std::cout << -1 << "\n";
      }
    }
  }

  void problem5() {
    int N = 0;
    std::cin >> N;
    for (int i = 1; i <= N; i *= 2) {
      std::cout << i << " ";
    }
    std::cout << "\n";
  }
  
  void problem6() {
    int N = 0;
    int count = 0;
    int number = 0;
    std::cin >> N;
    for (int i = 0; i < N; i++) {
      std::cin >> number;
      if (number > 0) {
        count = count + 1;
      }
    }
    std::cout << count << "\n";
  }
  
  void problem7() {
    int number = -1;
    int max_number = -1;
    int count = 0;
    for (;;) {
      std::cin >> number; 
      if (number == 0) {
        break;
      }
      if (number < 0) {
        continue;
      }
      if (number == max_number) {
        count = count + 1;
      }
      else if (number > max_number) {
        count = 1;
        max_number = number;
      }
    }
    std::cout << count << "\n";
  }
  
  void problem8() {
    class Laptop {
      public:
        Laptop(std::string input_brand, std::string input_model, double input_price) : brand(input_brand), model(input_model), price(input_price) {
          ltname = brand + " " + model;
        }

        std::string laptop_name() const {
          return ltname;
        }
      
      private:
        std::string brand;
        std::string model;
        double price;
        std::string ltname;
    };
  }

  /* ЗАДАЧА 9 */

  class Company; /* Director на неё ссылается */

  class Promise {
    public:
      Promise() : id(0), salary(0), paid(false) {}
      Promise(int input_id, float input_salary) : id(input_id), salary(input_salary), paid(false) {}

      int get_id() const { return id; }
      float get_salary() const { return salary; }
      bool get_promise() const { return paid; }

      void mark_paid() { paid = true; }
      void reset() { paid = false; }

    private:
      int id;
      float salary;
      bool paid;
  };

  class Director {
    public:
      Director(std::string input_name, std::string input_surname, int input_id, float input_salary)
        : name(input_name), surname(input_surname), promise(input_id, input_salary), company(nullptr) {}

      Promise& get_promise() { return promise; }
      void set_company(Company* c) { company = c; }

      bool check_promises() const;

    private:
      std::string name;
      std::string surname;
      Promise promise;
      Company* company;
  };

  class Employee {
    public:
      Employee(std::string input_name, std::string input_surname, int input_id, float input_salary)
        : name(input_name), surname(input_surname), promise(input_id, input_salary) {}

      Promise& get_promise() { return promise; }

    private:
      std::string name;
      std::string surname;
      Promise promise;
  };

  class Company {
    public:
      Company(float input_profit) : profit(input_profit), director_ptr(nullptr) {}

      ~Company() {
        delete director_ptr;
        for (auto* e : employees) delete e;
      }

      void create_director(std::string input_name, std::string input_surname, int input_id, float input_salary) {
        if (director_ptr != nullptr) {
          delete director_ptr;
        }
        director_ptr = new Director(input_name, input_surname, input_id, input_salary);
        director_ptr->set_company(this);
      }

      void create_employee(std::string input_name, std::string input_surname, int input_id, float input_salary) {
        employees.push_back(new Employee(input_name, input_surname, input_id, input_salary));
      }

      void set_profit(float value) {
        profit = value;
      }

      float get_profit() const {
        return profit;
      }

      Director& director() {
        return *director_ptr;
      }

      bool all_promises_paid() const {
        if (director_ptr != nullptr && !director_ptr->get_promise().get_promise()) {
          return false;
        }
        for (auto* e : employees) {
          if (!e->get_promise().get_promise()) return false;
        }
        return true;
      }

      bool fulfill_promise() {
        float total = 0;

        if (director_ptr != nullptr) {
          director_ptr->get_promise().reset();
          total += director_ptr->get_promise().get_salary();
        }
        for (auto* e : employees) {
          e->get_promise().reset();
          total += e->get_promise().get_salary();
        }

        if (total > profit) {
          return false;
        }

        if (director_ptr != nullptr) director_ptr->get_promise().mark_paid();
        for (auto* e : employees) e->get_promise().mark_paid();

        profit -= total;
        return true;
      }

    private:
      float profit;
      Director* director_ptr;
      std::vector<Employee*> employees;
  };

  inline bool Director::check_promises() const {
    return company != nullptr && company->all_promises_paid();
  }

  void problem9() {
    auto vk = Company(50);
    vk.create_director(
      "Владимир", "Кириенко", 1, 15);

    vk.create_employee(
      "Елена", "Иванова", 2, 8);

    vk.create_employee(
      "Виктор", "Кузнецов", 3, 6);

    vk.set_profit(145.12);
    vk.fulfill_promise();

    Director& director = vk.director();
    std::cout << (director.check_promises() ? "true" : "false") << "\n";

    vk.set_profit(-200);
    vk.fulfill_promise();

    std::cout << (director.check_promises() ? "true" : "false") << "\n";
  }
};

using namespace problem;

int main() {
  auto run_problem = [](this auto&& self) -> void
    {
        unsigned id_problem;
        std::cin >> id_problem;

        switch (id_problem) {
        case 1:
            problem1();
            break;

        case 2:
            problem2();
            break;
        
        case 3:
            problem3();
            break;
            
        case 4:
            problem4();
            break;
        
        case 5:
            problem5();
            break;

        case 6:
            problem6();
            break;

        case 7:
            problem7();
            break;

        case 8:
            problem8();
            break;

        case 9:
            problem9();
            break;

        default:
            self();
        }
    };

  run_problem();
}
