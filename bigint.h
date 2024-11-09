/*
    Basic bigint class. Bigint is represenred as a string.
*/


#include <iostream>
#include <string>

using namespace std;
class bigint
{
public:


    //-------------------------------------------------
    //------------Constructors for bigint--------------
    //-------------------------------------------------


    bigint()
    {
        bigint_str = "0";
    }
    bigint(int num)
    {
        this->bigint_str = to_string(num);
    }
    bigint(long int num)
    {
        this->bigint_str = to_string(num);
    }
    bigint(long long int num)
    {
        this->bigint_str = to_string(num);
    }
    bigint(string str)
    {
        this->bigint_str = str;
    }
    bigint(const char ch) 
    {
        this->bigint_str = string(1, ch);
    }
    bigint(const char *ch) 
    {
        this->bigint_str = string(ch);
    }
    bigint(const bigint& bigint)
    {
        bigint_str = bigint.bigint_str;
    }


    //-------------------------------------------------
    //---------------O P E R A T O R S-----------------
    //-------------------------------------------------


    const string operator+ (bigint& val) { return this->sum_s(bigint_str, val.bigint_str); }

    const string operator- (bigint& val) { return this->dif_s(bigint_str, val.bigint_str); }
    
    const string operator* (bigint& val) { return this->mul_s(bigint_str, val.bigint_str); }

    const string operator/ (bigint& val) { return this->div_s(bigint_str, val.bigint_str); }

    const string operator= (string& val)
    {
        this->bigint_str = val;
        return this->bigint_str;
    }

    
    const string operator= (int& val)
    {
        this->bigint_str = to_string(val);
        return this->bigint_str;
    }
    

    //-------------------------------------------------
    //--------F R I E N D   O P E R A T O R S----------
    //-------------------------------------------------


    friend bigint operator+(bigint const& a, int b)
    {
        return sum_s(a.bigint_str, std::to_string(b));
    }

    friend bigint operator+(int a, bigint const& b)
    {
        return sum_s(std::to_string(a), b.bigint_str);
    }

    friend bigint operator+(bigint const& a, string b)
    {
        return sum_s(a.bigint_str, b);
    }
    
    friend bigint operator+(string a, bigint const& b)
    {
        return sum_s(a, b.bigint_str);
    }

    friend bigint operator-(const bigint& a, int b)
    {
        return dif_s(a.bigint_str, std::to_string(b));
    }

    friend bigint operator-(int b, const bigint& a )
    {
        return dif_s(std::to_string(b), a.bigint_str);
    }
    
    friend bigint operator-(bigint const& a, string b)
    {
        return dif_s(a.bigint_str, b);
    }


    friend bigint operator-(string a, bigint const& b)
    {
        return dif_s(a, b.bigint_str);
    }

    friend bigint operator*(bigint const& a, string b)
    {
        return mul_s(a.bigint_str, b);
    }

    friend bigint operator*(string a, bigint const& b)
    {
        return mul_s(a, b.bigint_str);
    }

    friend bigint operator/(bigint const& a, string b)
    {
        return div_s(a.bigint_str, b);
    }

    friend bigint operator/(string a, bigint const& b)
    {
        return div_s(a, b.bigint_str);
    }

    friend bigint operator*(const bigint& a, int b)
    {
        return mul_s(a.bigint_str, std::to_string(b));
    }

    friend bigint operator*(int b, const bigint& a)
    {
        return mul_s( std::to_string(b), a.bigint_str);
    }

    friend bigint operator/(const bigint& a, int b)
    {
        return div_s(a.bigint_str, std::to_string(b));
    }

    friend bigint operator/(int b, const bigint& a)
    {
        return div_s(std::to_string(b), a.bigint_str);
    }

    friend std::ostream& operator << (std::ostream& stream, const bigint& val) {
        stream << val.bigint_str;
        return stream;
    }

    friend std::istream& operator >> (std::istream& stream, bigint& val) {
        stream >> val.bigint_str;
        return stream;
    }


    //-------------------------------------------------
    //----F U N C T I O N S    D E F I N I T I O N S---
    //-------------------------------------------------


    friend static const std::string pow(bigint& a, bigint& b)
    {
        return pow_s(a.bigint_str, b.bigint_str);
    }

    friend static const std::string pow(bigint& a, int b)
    {
        return pow_s(a.bigint_str, to_string(b));
    }

    friend static const std::string pow(int b, bigint& a)
    {
        return pow_s(to_string(b), a.bigint_str);
    }

    friend static const std::string pow(bigint& a, string b)
    {
        return pow_s(a.bigint_str, b);
    }

    friend static const std::string pow(string b, bigint& a)
    {
        return pow_s(b, a.bigint_str);
    }


    /* convert bigint obeject to std::string */
    static const std::string tos(bigint& a)
    {
        return a.bigint_str;
    }

    /* convert string of decimal numbers to string of binary numbers */
    static const string itobin(bigint& a) 
    {
        string str;
        str = a.bigint_str;
        int x;
        string sr;
        do {
            x = stoi(string(1, str[str.size() - 1]));
            sr.push_back('0' + (x & 1));
            str = shdivs(str, 2);
        } while (str != "0");
        reverse(sr.begin(), sr.end());
        return sr;
    }

    /* dividing a string by a number */
    static const string shdivs(string str, unsigned long long int divisor)
    {
        string sr;
        int idx = 0;
        long long int tmp = str[idx] - '0';

        while (tmp < divisor) {
            tmp = tmp * 10 + (str[++idx] - '0');
            if (idx >= str.size())
                break;
        }
        while (str.size() > idx) {
            sr += (tmp / divisor) + '0';
            tmp = (tmp % divisor) * 10 + str[++idx] - '0';
        }

        if (sr.size() == 0)
            return "0";

        return sr;
    }
    
    /* sum function */
    static const string sum_s(string a, string b)
    {
        string sr;
        unsigned n1, n2, sum, carry = 0;
        size_t sz1, sz2;
        if (a == "0") return b;
        if (b == "0") return a;
        sz1 = a.size(); sz2 = b.size();
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if (sz2 > sz1)
        {
            swap(a, b);
            sz1 = a.size(); sz2 = b.size();
        }
        for (int i = 0; i < sz2; i++)
        {
            n1 = a[i] - '0';
            n2 = b[i] - '0';
            sum = n1 + n2 + carry;
            sr += ((sum % 10) + '0');
            carry = sum / 10;
        }
        if (sz1 - sz2 != 0)
        {
            if (carry != 0)
            {
                for (size_t i = sz2; i < sz1; i++)
                {
                    n1 = a[i] - '0';
                    sum = n1 + carry;
                    sr += ((sum % 10) + '0');
                    carry = sum / 10;
                }
            }
            else
            {
                sr += a.substr(sz2, sz1 - sz2);
            }
        }
        else if (carry != 0) sr += carry + '0';
        if (sr[sr.size() - 1] == '0') sr += carry + '0';
        reverse(sr.begin(), sr.end());
        return sr;
    }
    
    /* difference function */
    static const string dif_s(string a, string b)
    {
        bool fl1 = true, fl2 = false, fl3 = true;
        // fl1 to delete zeros from the begining of string
        // fl2 to get negative number
        string sr, ac, bc;
        int n1, n2, df = 0, dif = 0;
        unsigned carry;
        size_t sz1, sz2;
        sz1 = a.size(); sz2 = b.size();
        if (sz1 == sz2) // determining the bigger number
        {
            if (a == b)
            {
                sr = "0";
                return sr;
            }
            while (fl3)
            {
                for (int i = 0; i < sz1; i++)
                {
                    if (a[i] == b[i]) continue;
                    n1 = a[i] - '0';
                    n2 = b[i] - '0';
                    if (n1 > n2)
                    {
                        fl3 = false;
                        break;
                    }
                    else
                    {
                        fl3 = false;
                        fl2 = true;
                        break;
                    }
                }
            }
        }

        if (sz2 > sz1 || fl2)
        {
            swap(a, b);
        }
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if (sz1 > sz2) b.append(sz1 - sz2, '0'); // adding zeros to reversed strings
        for (int i = 0; i < sz1; i++)
        {
            dif = (a[i] - '0') - (b[i] - '0') + df;
            if (dif < 0)
            {
                df = -1;
                carry = 10 + dif;
            }
            else
            {
                carry = dif;
                df = 0;
            }
            sr += (carry + '0');
        }
        while (fl1)
        {
            if (sr[sr.size() - 1] == '0') sr.erase(sr.size() - 1, 1);
            else fl1 = false;
        }
        if (fl2) sr.append(1, '-');
        reverse(sr.begin(), sr.end());
        return sr;
    }

    /* multiplication function */
    static const string mul_s(string a, string b)
    {
        string res, tmp, sr = "0";
        unsigned num, sz1, sz2, mul, carry = 0;
        sz1 = a.size(); sz2 = b.size();
        reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
        if (sz1 < sz2) swap(a, b);
        sz1 = a.size(); sz2 = b.size();
        for (int i = 0; i < sz2; i++)
        {
            for (int j = 0; j < sz1; j++)
            {
                mul = (b[i] - '0') * (a[j] - '0') + carry;
                num = mul % 10;
                carry = mul / 10;
                tmp += num + '0';
            }
            if (carry != 0) tmp += carry + '0';
            if (i > 0)
            {
                reverse(tmp.begin(), tmp.end());
                tmp.append(i, '0');
            }
            else reverse(tmp.begin(), tmp.end());
            sr = sum_s(sr, tmp);
            tmp = "";
        }
        return sr;
    }
    
    /* power function */
    static const string pow_s(string a, string b) 
    {
        string sr = "1";
        for (int i = 0; i < stoi(b); i++)
        {
            sr = mul_s(sr, a);
        }
        return sr;
    }

    /* division function */
    static const string div_s(string a, string b)
    {
        bool fl = false;
        string res, s1;
        const long long int l = INT64_MAX;
        unsigned tmp = 0, i = 1, n1 = 0, n2 = 0;
        int sz1, sz2, of = 0, c = 0;
        sz1 = a.size();
        sz2 = b.size();
        if (!(comp(a, to_string(l))))
        {
            n2 = stoll(a) / stoll(b);
            res = to_string(n2);
            return res;
        }
        else
        {
            for (i; i < sz1 + 1; i++)
            {

                if (fl)
                {
                    of = i - 1;
                    c = 1;
                    fl = false;
                }
                else c++;
                if (tmp != 0) s1 = to_string(tmp) + a.substr(of, c);
                else s1 = a.substr(of, c);
                if (comp(s1, b))
                {
                    tmp = stoi(s1) % stoi(b);
                    res += to_string(stoi(s1) / stoi(b));
                    fl = true;
                }
                else
                {
                    res += "0";
                    continue;
                }
            }
        }
        return del_zeros(res);
    }

    /* delete zeros in the begining of string */
    string const static del_zeros(string a)
    {
        unsigned i = 0;
        bool fl = true;
        while (fl == true)
        {
            if (a[i] == '0')
            {
                a.erase(i, 1);
            }
            else
            {
                fl = false;
                continue;
            }
        }
        return a;
    }

    /* comparing function */
    bool const static comp(string a, string b)
    {
        bool fl2 = true, fl1 = true;
        unsigned n1 = 0, n2 = 0;
        size_t sz1, sz2;
        sz1 = a.size();
        sz2 = b.size();
        if (sz1 > sz2)
        {
            fl2 = true;
            return fl2;
        }
        if (a == b)
        {
            fl2 = true;
            return fl2;
        }
        if (sz1 < sz2)
        {
            fl2 = false;
        }
        while (fl1)
        {
            for (int i = 0; i < sz1; i++)
            {
                if (a[i] == b[i]) continue;
                n1 = a[i] - '0';
                n2 = b[i] - '0';
                if (n1 > n2)
                {
                    fl2 = true;
                    fl1 = false;
                    break;
                }
                else
                {
                    fl1 = false;
                    fl2 = false;
                    break;
                }
            }
        }
        return fl2;
    }

private:
    string bigint_str;
    int bigint_int;
};