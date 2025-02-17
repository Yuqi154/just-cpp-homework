#include <iostream>


class Mat {
	/// <summary>
	/// 数据指针
	/// </summary>
	double* data;
	/// <summary>
	/// 矩阵行数和列数
	/// </summary>
	int R, C;
	/// <summary>
	/// 初始化矩阵并分配内存
	/// </summary>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	void alloc(int R, int C) {
		this->R = R;
		this->C = C;
		if (data != nullptr) {
			release();
		}
		data = new double[R * C];
	}
	/// <summary>
	/// 释放内存
	/// </summary>
	void release() {
		delete[] data;
	}
	/// <summary>
	/// 重新分配内存
	/// </summary>
	void realloc() {
		release();
		data = new double[R * C];
	}
	/// <summary>
	/// 使用0填充矩阵
	/// </summary>
	void clear() {
		memset(data, (double)0, R * C * sizeof(double));
	}
	/// <summary>
	/// 加载数据
	/// </summary>
	/// <param name="pData">一级指针指向的数据源</param>
	void load(double* pData) {
		memcpy(data, pData, R * C * sizeof(double));
	}
	/// <summary>
	/// 加载数据
	/// </summary>
	/// <param name="ppData">二级指针指向的数据源</param>
	void load(double** ppData) {
		for (int i = 0; i < R; i++) {
			memcpy(data + i * C, ppData[i], C * sizeof(double));
		}
	}
public:
	/// <summary>
	/// 构造函数
	/// </summary>
	Mat() {
		R = 0;
		C = 0;
		data = nullptr;
	}
	/// <summary>
	/// 带参构造函数
	/// </summary>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	Mat(int R, int C) {
		alloc(R, C);
	}
	/// <summary>
	/// 带参构造函数并加载数据
	/// </summary>
	/// <param name="pData">一级指针指向的数据源</param>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	Mat(double* pData, int R, int C) {
		alloc(R, C);
		load(pData);
	}
	/// <summary>
	/// 带参构造函数并加载数据
	/// </summary>
	/// <param name="ppData">二级指针指向的数据源</param>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	Mat(double** ppData, int R, int C) {
		alloc(R, C);
		load(ppData);
	}
	/// <summary>
	/// 带参构造函数并加载数据
	/// </summary>
	/// <param name="m">数据源矩阵</param>
	Mat(const Mat& m) {
		alloc(m.R, m.C);
		load(m.data);
	}
	/// <summary>
	/// 带参构造函数并加载数据
	/// </summary>
	/// <param name="m">数据源矩阵</param>
	/// <param name="r1">行数起始值</param>
	/// <param name="c1">列数起始值</param>
	/// <param name="r2">行数中止值</param>
	/// <param name="c2">列数中止值</param>
	Mat(const Mat& m, int r1, int c1, int r2, int c2) {
		alloc(r2 - r1 + 1, c2 - c1 + 1);
		for (int i = r1; i <= r2; i++) {
			memcpy(data + (i - r1) * C, m.data + i * m.C + c1, C * sizeof(double));
		}
	}
	/// <summary>
	/// <c>alloc</c>的别名
	/// </summary>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	void create(int R, int C) {
		alloc(R, C);
	}
	/// <summary>
	/// 加载数据
	/// </summary>
	/// <param name="pData">一级指针指向的数据源</param>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	void load(double* pData, int R, int C) {
		alloc(R, C);
		load(pData);
	}
	/// <summary>
	/// 加载数据
	/// </summary>
	/// <param name="ppData">二级指针指向的数据源</param>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	void load(double** ppData, int R, int C) {
		alloc(R, C);
		load(ppData);
	}
	/// <summary>
	/// 清空矩阵
	/// </summary>
	void destroy() {
		this->R = 0;
		this->C = 0;
		release();
	}
	/// <summary>
	/// 内存是否已经分配
	/// </summary>
	bool isAllocated() {
		return data != nullptr;
	}
	/// <summary>
	/// 将矩阵转换为一级指针
	/// </summary>
	/// <returns>一级指针，长度为R*C</returns>
	double* convertTo() {
		double* pData = new double[R * C];
		memcpy(pData, data, R * C * sizeof(double));
		return pData;
	}
	/// <summary>
	/// 复制矩阵
	/// </summary>
	/// <returns>复制后的矩阵</returns>
	Mat clone() {
		Mat m(R, C);
		m.load(data);
		return m;
	}
	/// <summary>
	/// 获取矩阵的单列
	/// </summary>
	/// <param name="c">列数</param>
	/// <returns>单列矩阵</returns>
	Mat getCol(int c) {
		Mat m(R, 1);
		for (int i = 0; i < R; i++) {
			m.data[i] = data[i * C + c];
		}
		return m;
	}
	/// <summary>
	/// 获取矩阵的行列
	/// </summary>
	/// <param name="r">行数</param>
	/// <returns>单行矩阵</returns>
	Mat getRow(int r) {
		Mat m(1, C);
		memcpy(m.data, data + r * C, C * sizeof(double));
		return m;
	}
	/// <summary>
	/// 设置矩阵的单列
	/// </summary>
	/// <param name="pData">一级指针指向的数据源</param>
	/// <param name="c">列数</param>
	void setCol(double* pData, int c) {
		for (int i = 0; i < R; i++) {
			data[i * C + c] = pData[i];
		}
	}
	/// <summary>
	/// 设置矩阵的单行
	/// </summary>
	/// <param name="pData">一级指针指向的数据源</param>
	/// <param name="r">行数</param>
	void setRow(double* pData, int r) {
		memcpy(data + r * C, pData, C * sizeof(double));
	}
	/// <summary>
	/// 获取矩阵的子矩阵
	/// </summary>
	/// <param name="r1">行数起始值</param>
	/// <param name="c1">列数起始值</param>
	/// <param name="r2">行数中止值</param>
	/// <param name="c2">列数中止值</param>
	/// <returns>子矩阵</returns>
	Mat GetSubMat(int r1, int c1, int r2, int c2) {
		Mat m(*this, r1, c1, r2, c2);
		return m;
	}
	/// <summary>
	/// 获取列数
	/// </summary>
	/// <returns>列数</returns>
	int cols() {
		return C;
	}
	/// <summary>
	/// 获取行数
	/// </summary>
	/// <returns>行数</returns>
	int rows() {
		return R;
	}
	/// <summary>
	/// 将矩阵复制到另一个矩阵
	/// </summary>
	/// <param name="m">目标矩阵</param>
	void copyTo(Mat& m) {
		m.create(R, C);
		m.load(data);
	}
	/// <summary>
	/// 将矩阵复制到另一个矩阵
	/// </summary>
	/// <param name="m">目标矩阵</param>
	/// <param name="r1">行数起始值</param>
	/// <param name="c1">列数起始值</param>
	/// <param name="r2">行数中止值</param>
	/// <param name="c2">列数中止值</param>
	void copyTo(Mat& m, int r1, int c1, int r2, int c2) {
		m.create(r2 - r1 + 1, c2 - c1 + 1);
		for (int i = r1; i <= r2; i++) {
			memcpy(m.data + (i - r1) * m.C, data + i * C + c1, m.C * sizeof(double));
		}
	}
	/// <summary>
	/// 获取矩阵对角线
	/// </summary>
	/// <returns>对角线矩阵</returns>
	Mat diag() {
		int n = R < C ? R : C;
		Mat m(n, 1);
		for (int i = 0; i < n; i++) {
			m.data[i] = data[i * C + i];
		}
		return m;
	}
	/// <summary>
	/// 创建单位矩阵
	/// </summary>
	/// <param name="n">矩阵阶数</param>
	/// <returns>单位矩阵</returns>
	static Mat eye(int n) {
		Mat m(n, n);
		m.clear();
		return m;
	}
	/// <summary>
	/// 创建全1矩阵
	/// </summary>
	/// <param name="R">行数</param>
	/// <param name="C">列数</param>
	/// <returns>全1矩阵</returns>
	static Mat ones(int R, int C) {
		Mat m(R, C);
		memset(m.data, (double)1, R * C * sizeof(double));
		return m;
	}
	/// <summary>
	/// 矩阵元素相加
	/// </summary>
	/// <returns>元素和</returns>
	double sum() {
		double s = 0;
		for (int i = 0; i < R * C; i++) {
			s += data[i];
		}
		return s;
	}
	/// <summary>
	/// 获取子矩阵元素和
	/// </summary>
	/// <param name="r1">行数起始值</param>
	/// <param name="c1">列数起始值</param>
	/// <param name="r2">行数中止值</param>
	/// <param name="c2">列数中止值</param>
	/// <returns>子矩阵元素和</returns>
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
	/// 获取矩阵行和
	/// </summary>
	/// <returns>行和</returns>
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
	/// 获取矩阵列和
	/// </summary>
	/// <returns>列和</returns>
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
	/// 获取矩阵数据
	/// </summary>
	/// <param name="r">行</param>
	/// <param name="c">列</param>
	/// <returns>数据</returns>
	double get(int r, int c) {
		return data[r * C + c];
	}
	/// <summary>
	/// 设置矩阵数据
	/// </summary>
	/// <param name="r">行</param>
	/// <param name="c">列</param>
	/// <param name="data">数据</param>
	void set(int r, int c, double data) {
		this->data[r * C + c] = data;
	}
	/// <summary>
	/// 矩阵转置
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
	/// 求和
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
	/// 求差
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
	/// 矩阵乘法
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
	/// 矩阵除法
	/// </summary>
	Mat div(const Mat& m) {
		return *this / m;
	}
	/// <summary>
	/// 是否是相同矩阵
	/// </summary>
	/// <param name="m">目标矩阵</param>
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
	/// 行拼接
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
	/// 列拼接
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