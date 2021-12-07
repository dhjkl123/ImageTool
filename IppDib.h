#pragma once
class IppDib
{
public:
	IppDib();
	IppDib(const IppDib& dib);
	~IppDib();

	IppDib& operator= (const IppDib & dib);

	BOOL CreatGrayBitmap(LONG nWidth, LONG nHeight);
	BOOL CreatRgbBitmap(LONG nWidth, LONG nHeight);
	void Destroy();

	BOOL Load(const char* filename);
	BOOL Save(const char* filename);

	BOOL LoadBMP(const char* filename);
	BOOL SaveBMP(const char* filename);

	void Draw(HDC hdc, int dx, int dy);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, DWORD dwRop);
	void Draw(HDC hdc, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop);

	BYTE* GetDIBitsAddr() const;
	int GetPaletteNums() const;

	LONG GetWidth() const { return m_nWidth; }
	LONG GetHeight() const { return m_nHeight; }
	WORD GetBitCount() const { return m_nBitCount; }
	DWORD GetDibSize() const { return m_nDibSize; }
	LPBITMAPINFO GetBitmapInfoAddr() const { return (LPBITMAPINFO)m_pDib; }
	BOOL IsValid() const { return (m_pDib != NULL); }

	int CopyToClipboard();
	int PasteFromClipboard();

private:
	LONG m_nWidth;		// ��Ʈ�� ���� ũ�� (�ȼ� ����)
	LONG m_nHeight;		// ��Ʈ�� ���� ũ�� (�ȼ� ����)
	WORD m_nBitCount;	// �ȼ� �� ��Ʈ ��
	DWORD m_nDibSize;	// DIB ��ü ũ��
	BYTE* m_pDib;		// DIB ���� �ּ�

	
};

