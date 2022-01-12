void BubbleSort(float m_array[], int m_length) {
    for (int a = 0; a < m_length - 1; a++) {
        for (int i = 0; i < m_length - 1; i++) {
            if (m_array[i] > m_array[i + 1]) {
                float t = m_array[i];
                m_array[i] = m_array[i + 1];
                m_array[i + 1] = t;
            }
        }
    }

}