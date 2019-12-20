#include "qlineeditip.h"
#include <QDebug>

QLineEditIP::QLineEditIP(QWidget *parent) : QLineEdit(parent)
{

}

void QLineEditIP::keyPressEvent(QKeyEvent *event)
{
    if(Qt::Key_0 <= event->key() && event->key() <= Qt::Key_9)
    {
        int num = event->key() - Qt::Key_0;
        QString data = QString().number(num) ;

        if(!this->selectedText().isEmpty())
        {
            IP = this->selectedText();
            if(IP == ".")return;

            QString L = this->text().mid(0,this->selectionStart()).remove(' ');
            QString R = this->text().mid(this->selectionStart() + IP.size()).remove(' ');;

            IP = this->text().replace(this->selectionStart(),IP.size(),data);
            IP.remove(' ');
            this->setText(shiftText(IP));

            setCursorPosition(insertTextPosition(L,data,R));
            return;
        }

        IP = this->text();
        int C = cursorPosition();

        if(C == IP.size())
        {
            IP.remove(' ');
            int n = IP.lastIndexOf('.');

            if(n > 0)
            {
                if((IP.mid(n + 1) + data).toInt() > 255)
                {
                    if(IP.split('.').size() >= 4)IP.append(data);
                    else
                    {
                        IP.append(".");
                        IP.append(data);
                    }
                }
                else if(IP.mid(n + 1).size() >= 3)
                {
                    if(IP.split('.').size() >= 4)IP.append(data);
                    else IP = IP.append(".") + data;
                }
                else IP.append(data);
            }
            else
            {
                if((IP + data).toInt() > 255)
                {
                    IP.append(".");
                    IP.append(data);
                }
                else if(IP.mid(n + 1).size() >= 3)
                {
                    IP = IP.append(".") + data;
                }
                else IP.append(data);

            }

            this->setText(shiftText(IP));
        }
        else
        {
            QString L = IP.mid(0,C).remove(' ');
            QString R = IP.mid(C).remove(' ');

            IP = L + data + R;
            this->setText(shiftText(IP));
            setCursorPosition(insertTextPosition(L,data ,R));
        }

    }
    else if(event->key() == Qt::Key_Backspace)
    {
        if(!this->selectedText().isEmpty())
        {
            IP = this->selectedText();
            if(IP == ".")return;

            QString L = this->text().mid(0,this->selectionStart()).remove(' ');
            QString R = this->text().mid(this->selectionStart() + IP.size()).remove(' ');;

            IP = this->text().replace(this->selectionStart(),IP.size(),"");
            IP.remove(' ');
            this->setText(shiftText(IP));
            setCursorPosition(insertTextPosition(L,"",R));
            return;
        }

        IP = text();
        int C = cursorPosition();
        if(C <=0)return;
        QString L = text().mid(0,C);
        if(L.right(1).at(0) == ' ' || L.right(1).at(0) == '.')return;

        QLineEdit::keyPressEvent(event);
    }
    else if(event->key() == Qt::Key_Period)
    {
        if(text().split('.').size() >= 4)return;

        if(cursorPosition() != text().size())return;

        QStringList list;
        QString str;
        QString IP1;
        QString IP2;
        QString IP3;
        QString IP4;

        IP = text();
        list = IP.remove(' ').split('.');

        int i = 0;

        for(; i < list.size() ;i++ )
        {
            switch(i)
            {
                case 0:
                {
                    IP1 = shift(list.at(0));

                    if(IP1.size() <= 0) break;
                    if(IP1.left(1).at(0) == ' ')IP1.remove(0,1);

                    str.append(IP1 + space + ".");
                    break;
                }
                case 1:
                {
                    IP2 = shift(list.at(1));
                    if(IP2.isEmpty())IP2 = " 0 ";

                    str.append(IP2 + space + ".");
                    break;
                }
                case 2:
                {
                    IP3 = shift(list.at(2));
                    if(IP3.isEmpty())IP3 = " 0 ";

                    str.append(IP3 + space + ".");
                    break;
                }
                case 3:
                {
                    IP4 = shift(list.at(3));
                    if(IP4.isEmpty())IP4 = " 0 ";

                    str.append(IP4 + space + ".");
                    break;
                }
            }
        }

        setText(str);
    }
    else if(event->key() == Qt::Key_Left)
    {
        IP = text();
        int i = 0;
        bool flag = false;
        int C = cursorPosition();

        if(C <= 1)
        {
            QLineEdit::keyPressEvent(event);
            return;
        }

        QString L = text().mid(0,C);

        if(L.right(i + 1).at(0) == ' ' || L.right(i + 1).at(0) == '.')
        {
            while(1)
            {
                if(L.right(i + 1).at(0) == ' ')
                {
                    if(flag)
                    {
                        if(i + space.size() >= L.size()) setCursorPosition(C - L.size());
                        else setCursorPosition(C - (i + space.size()));
                        return;
                    }

                    i++;
                    if(i >= L.size()) {setCursorPosition(C - L.size());return;}
                }
                else if(L.right(i + 1).at(0) == '.')
                {
                    if(flag)
                    {
                        if(i + space.size() >= L.size()) setCursorPosition(C - L.size());
                        else setCursorPosition(C - (i + space.size()));
                        return;
                    }

                    flag = true;
                    i++;
                    if(i >= L.size()) {setCursorPosition(C - L.size());return;}
                }
                else
                {
                    setCursorPosition(C - i);
                    break;
                }

            }
        }
        else QLineEdit::keyPressEvent(event);
    }
    else if(event->key() == Qt::Key_Right)
    {
        IP = text();
        int C = cursorPosition();

        if(C >= IP.size())
        {
            QLineEdit::keyPressEvent(event);
            return;
        }

        QString R = text().mid(C);
        if(R.left(1).right(1).at(0) == ' ' || R.left(1).right(1).at(0) == '.')
        {
            setCursorPosition( rightMove(text(),C));
        }
        else QLineEdit::keyPressEvent(event);
    }
    else if(event->key() == Qt::Key_Delete)
    {
        if(!this->selectedText().isEmpty())
        {
            IP = this->selectedText();
            if(IP == ".")return;

            QString L = this->text().mid(0,this->selectionStart()).remove(' ');
            QString R = this->text().mid(this->selectionStart() + IP.size()).remove(' ');;

            IP = this->text().replace(this->selectionStart(),IP.size(),"");
            IP.remove(' ');
            this->setText(shiftText(IP));
            setCursorPosition(insertTextPosition(L,"",R));
            return;
        }

        IP = text();
        int C = cursorPosition();

        if(C >= IP.size())return;

        QString R = text().mid(C);
        if(R.left(1).at(0) == ' ' || R.left(1).at(0) == '.')return;

        QLineEdit::keyPressEvent(event);
    }
    else if(event == QKeySequence::Copy) //ctrl + C 进入这里
    {
        QLineEdit::keyPressEvent(event);
    }
}

int QLineEditIP::rightMove(QString tr,int C)
{
    if(tr.size() == C)return C;

    QString R = tr.mid(C);
    int i = 0;
    bool flag = false;

    while(1)
    {
        if(R.left(i + 1).right(1).at(0) == ' ')
        {
            if(flag)
            {
                if(i + space.size() >= R.size())
                    return C + R.size();
                else return C + i + space.size();
            }

            i++;
            if(i >= R.size())
                return C + R.size();
        }
        else if(R.left(i + 1).right(1).at(0) == '.')
        {
            if(flag)
            {
                if(i + space.size() >= R.size())
                    return C + R.size();
                else return C + i + space.size();
            }

            flag = true;
            i++;

            if(i >= R.size())
                return C + R.size();
        }
        else
        {
            return C + i;
        }

    }

}

void QLineEditIP::setFont(QFont &F) //根据控件大小，设置字体大小
{
    QLineEdit::setFont(F);

    int W;

    while(1)
    {
        QFontMetrics fontWidth(F);
        W = fontWidth.width(".");  //计算字符串宽度
        int t_W = width() - 3*W;

        if(W*12 >= t_W)  //当字符串宽度大于最大宽度时进行转换
        {
            int S = F.pointSize();

            if(S <= 7)
            {
                int num = ((t_W / 4) - 3*W)/W/ 2;

                for(int i = 0 ; i < num ; i++)
                    space.append(" ");
                return;
            }


            F.setPointSize(S -1);
            QLineEdit::setFont(F);
        }
        else
        {
            int num = ((t_W / 4) - 3*W)/W/ 2;

            for(int i = 0 ; i < num ; i++)
                space.append(" ");
            return;
        }
    }
}

QString QLineEditIP::shiftText(QString str) //返回格式编排好的Qstring
{
    if(str.isEmpty())return "";

    QStringList list;

    QString IP1;
    QString IP2;
    QString IP3;
    QString IP4;

    while(1)
    {
        list = str.split('.');

        str.clear();

        int i = 0;

        for(; i < list.size() ;i++ )
        {
            switch(i)
            {
            case 0:
            {
                IP1 = shift(list.at(0));

                if(IP1.size() <= 0) break;
                if(IP1.left(1).at(0) == ' ')IP1.remove(0,1);

                str.append(IP1);
                break;
            }
            case 1:
            {
                IP2 = shift(list.at(1));
                str.append(space + "." + space + IP2);
                break;
            }
            case 2:
            {
                IP3 = shift(list.at(2));
                str.append(space + "." + space + IP3);
                break;
            }
            case 3:
            {
                IP4 = shift(list.at(3));
                str.append(space + "." +  space + IP4);
                break;
            }
            }
        }

        if(str.right(1).at(0) == ' ')str.remove(str.size() - 1,1);
        return str;
    }
}

int QLineEditIP::insertTextPosition(QString str ,QString data ,QString str2)//返回插入数据改变后的坐标，尾部插入不需要调用这个函数
{
    if(str.isEmpty())
    {
        return 1;
    }

    QStringList list;

    QString IPStr;

    while(1)
    {
        list = str.split('.');

        str.clear();

        int i = 0;

        for(; i < list.size() - 1 ;i++ )
        {
            switch(i)
            {
                case 0:
                {
                    IPStr = shift(list.at(0));

                    if(IPStr.size() <= 0) break;
                    if(IPStr.left(1).at(0) == ' ')IPStr.remove(0,1);

                    str.append(IPStr + space + "." + space);
                    break;
                }
                case 1:
                {
                    IPStr = shift(list.at(1));
                    str.append( IPStr + space + "." + space);
                    break;
                }
                case 2:
                {
                    IPStr = shift(list.at(2));
                    str.append(IPStr + space + "." + space);
                    break;
                }
                case 3:
                {
                    IPStr = shift(list.at(3));
                    str.append(IPStr);
                    break;
                }
            }
        }

        QString strdata = list.at(i) + data;

        if(!str2.isEmpty() &&  str2.left(1).at(0) == '.')
        {
            if(strdata.size() >= 3 )
            {
                return str.size() + 3 + (space.size() * 2) + 1;
            }
            else if(strdata.size() == 1)return str.size() + strdata.size() + 1;
            else return str.size() + strdata.size();

        }
        else if(strdata.size() == 1) return str.size() + strdata.size() + 1;
        else return str.size() + strdata.size();
    }
}

QString QLineEditIP::shift(QString tr)
{
    int num = tr.length();

    if(tr.toInt() > 255)return tr = "255";
    else if(num > 3)
    {
        while(1)
        {
            if(tr.left(1).at(0) == '0')tr = tr.mid(1);
            if(tr.length() <= 3)break;
        }
    }

    switch(num)
    {
        case 0 : tr =  "";break;
        case 1 : tr =  " " + tr + " ";break;
        case 2 : tr =  tr+" ";break;
        case 3 : break;
    }

    return tr;
}

QString QLineEditIP::insertShift(QString tr)
{
    int num = tr.length();

    if(tr.toInt() > 255)return tr = "255";

    switch(num)
    {
        case 0 : tr =  "";break;
        case 1 : tr =  " " + tr;break;
        case 2 : tr =  tr;break;
        case 3 : break;
    }

    return tr;
}
