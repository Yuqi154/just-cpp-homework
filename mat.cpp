#include <iostream>


class Mat {
	/// <summary>
	/// ����ָ��
	/// </summary>
	double* data;
	/// <summary>
	/// ��������������
	/// </summary>
	int R, C;
	/// <summary>
	/// ��ʼ�����󲢷����ڴ�
	/// </summary>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	void alloc(int R, int C) {
		this->R = R;
		this->C = C;
		if (data != nullptr) {
			release();
		}
		data = new double[R * C];
	}
	/// <summary>
	/// �ͷ��ڴ�
	/// </summary>
	void release() {
		delete[] data;
	}
	/// <summary>
	/// ���·����ڴ�
	/// </summary>
	void realloc() {
		release();
		data = new double[R * C];
	}
	/// <summary>
	/// ʹ��0������
	/// </summary>
	void clear() {
		memset(data, (double)0, R * C * sizeof(double));
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="pData">һ��ָ��ָ�������Դ</param>
	void load(double* pData) {
		memcpy(data, pData, R * C * sizeof(double));
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="ppData">����ָ��ָ�������Դ</param>
	void load(double** ppData) {
		for (int i = 0; i < R; i++) {
			memcpy(data + i * C, ppData[i], C * sizeof(double));
		}
	}
public:
	/// <summary>
	/// ���캯��
	/// </summary>
	Mat() {
		R = 0;
		C = 0;
		data = nullptr;
	}
	/// <summary>
	/// ���ι��캯��
	/// </summary>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	Mat(int R, int C) {
		alloc(R, C);
	}
	/// <summary>
	/// ���ι��캯������������
	/// </summary>
	/// <param name="pData">һ��ָ��ָ�������Դ</param>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	Mat(double* pData, int R, int C) {
		alloc(R, C);
		load(pData);
	}
	/// <summary>
	/// ���ι��캯������������
	/// </summary>
	/// <param name="ppData">����ָ��ָ�������Դ</param>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	Mat(double** ppData, int R, int C) {
		alloc(R, C);
		load(ppData);
	}
	/// <summary>
	/// ���ι��캯������������
	/// </summary>
	/// <param name="m">����Դ����</param>
	Mat(const Mat& m) {
		alloc(m.R, m.C);
		load(m.data);
	}
	/// <summary>
	/// ���ι��캯������������
	/// </summary>
	/// <param name="m">����Դ����</param>
	/// <param name="r1">������ʼֵ</param>
	/// <param name="c1">������ʼֵ</param>
	/// <param name="r2">������ֵֹ</param>
	/// <param name="c2">������ֵֹ</param>
	Mat(const Mat& m, int r1, int c1, int r2, int c2) {
		alloc(r2 - r1 + 1, c2 - c1 + 1);
		for (int i = r1; i <= r2; i++) {
			memcpy(data + (i - r1) * C, m.data + i * m.C + c1, C * sizeof(double));
		}
	}
	/// <summary>
	/// <c>alloc</c>�ı���
	/// </summary>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	void create(int R, int C) {
		alloc(R, C);
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="pData">һ��ָ��ָ�������Դ</param>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	void load(double* pData, int R, int C) {
		alloc(R, C);
		load(pData);
	}
	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="ppData">����ָ��ָ�������Դ</param>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	void load(double** ppData, int R, int C) {
		alloc(R, C);
		load(ppData);
	}
	/// <summary>
	/// ��վ���
	/// </summary>
	void destroy() {
		this->R = 0;
		this->C = 0;
		release();
	}
	/// <summary>
	/// �ڴ��Ƿ��Ѿ�����
	/// </summary>
	bool isAllocated() {
		return data != nullptr;
	}
	/// <summary>
	/// ������ת��Ϊһ��ָ��
	/// </summary>
	/// <returns>һ��ָ�룬����ΪR*C</returns>
	double* convertTo() {
		double* pData = new double[R * C];
		memcpy(pData, data, R * C * sizeof(double));
		return pData;
	}
	/// <summary>
	/// ���ƾ���
	/// </summary>
	/// <returns>���ƺ�ľ���</returns>
	Mat clone() {
		Mat m(R, C);
		m.load(data);
		return m;
	}
	/// <summary>
	/// ��ȡ����ĵ���
	/// </summary>
	/// <param name="c">����</param>
	/// <returns>���о���</returns>
	Mat getCol(int c) {
		Mat m(R, 1);
		for (int i = 0; i < R; i++) {
			m.data[i] = data[i * C + c];
		}
		return m;
	}
	/// <summary>
	/// ��ȡ���������
	/// </summary>
	/// <param name="r">����</param>
	/// <returns>���о���</returns>
	Mat getRow(int r) {
		Mat m(1, C);
		memcpy(m.data, data + r * C, C * sizeof(double));
		return m;
	}
	/// <summary>
	/// ���þ���ĵ���
	/// </summary>
	/// <param name="pData">һ��ָ��ָ�������Դ</param>
	/// <param name="c">����</param>
	void setCol(double* pData, int c) {
		for (int i = 0; i < R; i++) {
			data[i * C + c] = pData[i];
		}
	}
	/// <summary>
	/// ���þ���ĵ���
	/// </summary>
	/// <param name="pData">һ��ָ��ָ�������Դ</param>
	/// <param name="r">����</param>
	void setRow(double* pData, int r) {
		memcpy(data + r * C, pData, C * sizeof(double));
	}
	/// <summary>
	/// ��ȡ������Ӿ���
	/// </summary>
	/// <param name="r1">������ʼֵ</param>
	/// <param name="c1">������ʼֵ</param>
	/// <param name="r2">������ֵֹ</param>
	/// <param name="c2">������ֵֹ</param>
	/// <returns>�Ӿ���</returns>
	Mat GetSubMat(int r1, int c1, int r2, int c2) {
		Mat m(*this, r1, c1, r2, c2);
		return m;
	}
	/// <summary>
	/// ��ȡ����
	/// </summary>
	/// <returns>����</returns>
	int cols() {
		return C;
	}
	/// <summary>
	/// ��ȡ����
	/// </summary>
	/// <returns>����</returns>
	int rows() {
		return R;
	}
	/// <summary>
	/// �������Ƶ���һ������
	/// </summary>
	/// <param name="m">Ŀ�����</param>
	void copyTo(Mat& m) {
		m.create(R, C);
		m.load(data);
	}
	/// <summary>
	/// �������Ƶ���һ������
	/// </summary>
	/// <param name="m">Ŀ�����</param>
	/// <param name="r1">������ʼֵ</param>
	/// <param name="c1">������ʼֵ</param>
	/// <param name="r2">������ֵֹ</param>
	/// <param name="c2">������ֵֹ</param>
	void copyTo(Mat& m, int r1, int c1, int r2, int c2) {
		m.create(r2 - r1 + 1, c2 - c1 + 1);
		for (int i = r1; i <= r2; i++) {
			memcpy(m.data + (i - r1) * m.C, data + i * C + c1, m.C * sizeof(double));
		}
	}
	/// <summary>
	/// ��ȡ����Խ���
	/// </summary>
	/// <returns>�Խ��߾���</returns>
	Mat diag() {
		int n = R < C ? R : C;
		Mat m(n, 1);
		for (int i = 0; i < n; i++) {
			m.data[i] = data[i * C + i];
		}
		return m;
	}
	/// <summary>
	/// ������λ����
	/// </summary>
	/// <param name="n">�������</param>
	/// <returns>��λ����</returns>
	static Mat eye(int n) {
		Mat m(n, n);
		m.clear();
		return m;
	}
	/// <summary>
	/// ����ȫ1����
	/// </summary>
	/// <param name="R">����</param>
	/// <param name="C">����</param>
	/// <returns>ȫ1����</returns>
	static Mat ones(int R, int C) {
		Mat m(R, C);
		memset(m.data, (double)1, R * C * sizeof(double));
		return m;
	}
	/// <summary>
	/// ����Ԫ�����
	/// </summary>
	/// <returns>Ԫ�غ�</returns>
	double sum() {
		double s = 0;
		for (int i = 0; i < R * C; i++) {
			s += data[i];
		}
		return s;
	}
	/// <summary>
	/// ��ȡ�Ӿ���Ԫ�غ�
	/// </summary>
	/// <param name="r1">������ʼֵ</param>
	/// <param name="c1">������ʼֵ</param>
	/// <param name="r2">������ֵֹ</param>
	/// <param name="c2">������ֵֹ</param>
	/// <returns>�Ӿ���Ԫ�غ�</returns>
	double sum(int r1, int c1, int r2, int c2) {
		double s = 0;
		for (int i = r1; i <= r2; i++) {
			for (int j = c1; j <= c2; j++) {
				s += data[i * C + j];
			}
		}
		return s;
	}
	/// <summary>
	/// ��ȡ�����к�
	/// </summary>
	/// <returns>�к�</returns>
	double* sumInRow() {
		double* s = new double[R];
		for (int i = 0; i < R; i++) {
			s[i] = 0;
			for (int j = 0; j < C; j++) {
				s[i] += data[i * C + j];
			}
		}
		return s;
	}
	/// <summary>
	/// ��ȡ�����к�
	/// </summary>
	/// <returns>�к�</returns>
	double* sumInCol() {
		double* s = new double[C];
		for (int j = 0; j < C; j++) {
			s[j] = 0;
			for (int i = 0; i < R; i++) {
				s[j] += data[i * C + j];
			}
		}
		return s;
	}
	/// <summary>
	/// ��ȡ��������
	/// </summary>
	/// <param name="r">��</param>
	/// <param name="c">��</param>
	/// <returns>����</returns>
	double get(int r, int c) {
		return data[r * C + c];
	}
	/// <summary>
	/// ���þ�������
	/// </summary>
	/// <param name="r">��</param>
	/// <param name="c">��</param>
	/// <param name="data">����</param>
	void set(int r, int c, double data) {
		this->data[r * C + c] = data;
	}
	/// <summary>
	/// ����ת��
	/// </summary>
	Mat inverse() {
		Mat m(R, C);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				m.data[j * R + i] = data[i * C + j];
			}
		}
		return m;
	}
	Mat operator+(const Mat& m) {
		Mat n(R, C);
		for (int i = 0; i < R * C; i++) {
			n.data[i] = data[i] + m.data[i];
		}
		return n;
	}
	/// <summary>
	/// ���
	/// </summary>
	Mat plus(const Mat& m) {
		return *this + m;
	}
	Mat operator-(const Mat& m) {
		Mat n(R, C);
		for (int i = 0; i < R * C; i++) {
			n.data[i] = data[i] - m.data[i];
		}
		return n;
	}
	/// <summary>
	/// ���
	/// </summary>
	Mat minus(const Mat& m) {
		return *this - m;
	}
	Mat operator*(const Mat& m) {
		Mat n(R, m.C);
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < m.C; j++) {
				n.data[i * m.C + j] = 0;
				for (int k = 0; k < C; k++) {
					n.data[i * m.C + j] += data[i * C + k] * m.data[k * m.C + j];
				}
			}
		}
		return n;
	}
	/// <summary>
	/// ����˷�
	/// </summary>
	Mat mult(const Mat& m) {
		return *this * m;
	}
	Mat operator/(const Mat& m) {
		Mat n(R, C);
		for (int i = 0; i < R * C; i++) {
			n.data[i] = data[i] / m.data[i];
		}
		return n;
	}
	/// <summary>
	/// �������
	/// </summary>
	Mat div(const Mat& m) {
		return *this / m;
	}
	/// <summary>
	/// �Ƿ�����ͬ����
	/// </summary>
	/// <param name="m">Ŀ�����</param>
	bool same(const Mat& m) {
		if (R != m.R || C != m.C) {
			return false;
		}
		for (int i = 0; i < R * C; i++) {
			if (data[i] != m.data[i]) {
				return false;
			}
		}
		return true;
	}
	/// <summary>
	/// ��ƴ��
	/// </summary>
	Mat matchInRow(const Mat& m) {
		if (R != m.R) {
			return Mat();
		}
		Mat n(R, C + m.C);
		for (int i = 0; i < R; i++) {
			memcpy(n.data + i * (C + m.C), data + i * C, C * sizeof(double));
			memcpy(n.data + i * (C + m.C) + C, m.data + i * m.C, m.C * sizeof(double));
		}
		return n;
	}
	/// <summary>
	/// ��ƴ��
	/// </summary>
	Mat matchInCow(const Mat& m) {
		if (C != m.C) {
			return Mat();
		}
		Mat n(R + m.R, C);
		memcpy(n.data, data, R * C * sizeof(double));
		memcpy(n.data + R * C, m.data, m.R * m.C * sizeof(double));
		return n;
	}

	Mat& operator=(const Mat& m) {
		if (this == &m) {
			return *this;
		}
		alloc(m.R, m.C);
		load(m.data);
		return *this;
	}

};