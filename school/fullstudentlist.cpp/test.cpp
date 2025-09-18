void RemoveStudentByName(PTR &head, string name) {
    // Trường hợp node đầu tiên trùng tên
    while (head != NULL && head->st.name == name) {
        PTR temp = head;
        head = head->next;
        delete temp;
    }

    // Duyệt các node còn lại
    PTR prev = head;
    while (prev != NULL && prev->next != NULL) {
        if (prev->next->st.name == name) {
            PTR temp = prev->next;
            prev->next = temp->next;  // nối qua node bị xóa
            delete temp;
        } else {
            prev = prev->next;        // dịch prev đi tiếp
        }
    }
}
