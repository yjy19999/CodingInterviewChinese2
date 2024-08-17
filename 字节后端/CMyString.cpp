#include <cstring>
#include <cstdio>

class CMyString0
{
public:
    CMyString0(char* pData=nullptr){}
    CMyString0(const CMyString0& str){}
    ~CMyString0(void){}
    const CMyString0& operator=(const CMyString0& str)
    {
        return *this;
    }
private:
    char* m_pData;
};

class CMyString3
{
private:
    char* m_pData;
public:
    // CMyString1(char* pData=nullptr){}
    CMyString3(){}
    CMyString3(char* pData)
    {
        if(pData==nullptr) 
        {
            m_pData=nullptr;
            return;
        }
        m_pData=new char[strlen(pData)+1];
        strcpy(m_pData,pData);
    }
    CMyString3(const CMyString3& str){}
    ~CMyString3(void){}
    void printStr()
    {
        printf("%s\n",m_pData);
    }
    const CMyString3& operator=(const CMyString3& str)
    {
        if(this==&str)
        {
            return *this;
        }
        delete []m_pData;
        m_pData=nullptr;

        m_pData=new char[strlen(str.m_pData)+1];
        strcpy(m_pData,str.m_pData);
        return *this;
    }
};

class CMyString3
{
private:
    char* m_pData;
public:
    // CMyString1(char* pData=nullptr){}
    CMyString3(){}
    CMyString3(char* pData)
    {
        if(pData==nullptr) 
        {
            m_pData=nullptr;
            return;
        }
        m_pData=new char[strlen(pData)+1];
        strcpy(m_pData,pData);
    }
    CMyString3(const CMyString3& str){}
    ~CMyString3(void){}
    void printStr()
    {
        printf("%s\n",m_pData);
    }
    const CMyString3& operator=(const CMyString3& str)
    {
        if(this==&str)
        {
            return *this;
        }
        m_pData=new char[strlen(str.m_pData)+1];
        if(m_pData!=nullptr)
        {
            strcpy(m_pData,str.m_pData);
            delete []m_pData;
            m_pData=nullptr;
        }
        else
        {
            //
        }
        return *this;
    }
};

class CMyString3
{
private:
    char* m_pData;
public:
    // CMyString1(char* pData=nullptr){}
    CMyString3(){}
    CMyString3(char* pData)
    {
        if(pData==nullptr) 
        {
            m_pData=nullptr;
            return;
        }
        m_pData=new char[strlen(pData)+1];
        strcpy(m_pData,pData);
    }
    CMyString3(const CMyString3& str){}
    ~CMyString3(void){}
    void printStr()
    {
        printf("%s\n",m_pData);
    }
    const CMyString3& operator=(const CMyString3& str)
    {
        if(this==&str)
        {
            return *this;
        }
        CMyString3 strTemp(str);
        char* pTemp=strTemp.m_pData;
        strTemp.m_pData=m_pData;
        m_pData=pTemp;
        return *this;
    }
};

int main()
{
    CMyString0 str0=CMyString0();
    char arr[]="hello";
    CMyString3 str1=CMyString3(arr);
    CMyString3 str3,str2;
    str3=str2=str1;
    str3.printStr();
    str2.printStr();
    str1.printStr();
}