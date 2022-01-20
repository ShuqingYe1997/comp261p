template <typename Object>
class Node {
    public:
        Object value;
        Node<Object>* next;

        Node() {
            value = nullptr;
            next = nullptr;
        }

        Node(const Object value_param, Node<Object>* next_param = nullptr) {
            value = value_param;
            next = next_param;
        }

        ~Node() {

        }
};