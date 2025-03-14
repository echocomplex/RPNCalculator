#include "RPNCalculator.hxx"

unsigned short priority (char oper) {
    if (oper == '+' or oper == '-') return 1;
    else if (oper == '*' or oper == '/') return 2;
    else return 0;
}


int translateToRPN (std::vector<std::string>& queue, const std::string& exercise) {
    if (
        (std::count(exercise.begin(), exercise.end(), '(') != std::count(exercise.begin(), exercise.end(), ')')) ||
        (std::count(exercise.begin(), exercise.end(), '[') != std::count(exercise.begin(), exercise.end(), ']')) ||
        (std::count(exercise.begin(), exercise.end(), '{') != std::count(exercise.begin(), exercise.end(), '}'))
    ) {
        std::cerr << "Brackets error" << std::endl;
        return 1;
    }

    std::stack <char> operators;
    std::map <char, char> brackets = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };
    
    for (size_t i = 0; i < exercise.size(); ++i) {
        if (exercise[i] == ' ') continue;

        if (exercise[i] >= 48 && exercise[i] <= 57) {
            std::string num;;
            for (;i < exercise.size() && (exercise[i] >= 48 && exercise[i] <= 57); ++i) {
                num.push_back(exercise[i]);
            }
            --i;

            queue.push_back(num);
        }
        else if (exercise[i] == '-' && (i == 0 || exercise[i - 1] == '(' || exercise[i - 1] == '[' || exercise[i - 1] == '{')) {
            std::string num = "-";
            ++i;
            for (;i < exercise.size() && (exercise[i] >= 48 && exercise[i] <= 57); ++i) {
                num.push_back(exercise[i]);
            }
            --i;
            queue.push_back(num);
        }
        else if (exercise[i] == '+' || exercise[i] == '-' || exercise[i] == '*' || exercise[i] == '/') {
            while (!operators.empty() && priority(operators.top()) >= priority(exercise[i])) {
                std::string op(1, operators.top());
                queue.push_back(op);
                operators.pop();
            }
            operators.push(exercise[i]);
        }
        else if ((exercise[i] == '(' || exercise[i] == '{' || exercise[i] == '[')) {
            operators.push(exercise[i]);
        }
        else if ((exercise[i] == ')' || exercise[i] == '}' || exercise[i] == ']')) {
            while (!operators.empty() && operators.top() != brackets[exercise[i]]) {
                std::string op(1, operators.top());
                queue.push_back(op); operators.pop();
            }
            operators.pop();
        }
        else break;
    }

    while (!operators.empty()) {
        std::string op(1, operators.top());
        queue.push_back(op); operators.pop();
    }

    return 0;
}


long long calculate (const std::vector<std::string>& queue) {
    std::stack <long long> nums;
    for (size_t i = 0; i < queue.size(); ++i) {
        if (queue[i] == "+") {
            int second = nums.top(); nums.pop();
            int first = nums.top(); nums.pop();
            nums.push(first + second);
        }
        else if (queue[i] == "-") {
            int second = nums.top(); nums.pop();
            int first = nums.top(); nums.pop();
            nums.push(first - second);
        }
        else if (queue[i] == "*") {
            int second = nums.top(); nums.pop();
            int first = nums.top(); nums.pop();
            nums.push(first * second);
        }
        else if (queue[i] == "/") {
            int second = nums.top(); nums.pop();
            int first = nums.top(); nums.pop();
            nums.push(first / second);
        }
        else nums.push(std::stoll(queue[i]));
    }
    return nums.top();
}