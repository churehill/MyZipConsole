#include <QtCore/QCoreApplication>
#include <QString>
#include <QTextCodec>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include "quazip/JlCompress.h"
#include <iostream>


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    if(argc<=1||(argc>1&&QString::fromAscii(argv[1])=="-h"))
    {
        cout<<endl
          <<"**************************MyZip Console Edition*************************"<<endl<<endl
          <<"                                 provided by Lu Xinchang. AKA: Churehill"<<endl
          <<"                                              ��¬�γ�����,����ҵ--MyZIP"<<endl<<endl
          <<"�÷���"<<"MyZip [-f FileToCompress ZIPFile] [-d DirToCompress ZIPFile] "<<endl
          <<"           "<<"[-h] [-u ZIPFile DirToPut] [-ul ZIPFile]"<<endl<<endl
          <<"ѡ�"<<endl
          <<"-f      "<<"ѹ���ļ����ڶ���������Ҫѹ�����ļ��ľ���·����������������\n"
          <<"        "<<"���ɵ�ѹ���ļ���Ҫ���õ�·�����ļ����֣������Ǿ��Ի����·��\n\n"
          <<"-d      "<<"ѹ��Ŀ¼���ڶ���������Ҫѹ����Ŀ¼�ľ���·����������������\n"
          <<"        "<<"���ɵ�ѹ���ļ���Ҫ���õ�·�����ļ����֣������Ǿ��Ի����·��\n\n"
          <<"-u      "<<"��ѹzip�ļ����ڶ�������zip�ļ��ľ���·�����ļ�����������������\n"
          <<"        "<<"��ѹ��Ҫ���õ�Ŀ¼�������Ǿ��Ի����·��\n\n"
          <<"-ul     "<<"��ѹzip�ļ��������ڵ��ļ��У��ڶ�������zip�ļ��ľ���·�����ļ���\n\n"
          <<"-h      "<<"�鿴����\n"<<endl;
          return 1;
    }
    if(argc>1)
    {
        //QString pram="-f";
        QString pram(argv[1]);
        if(pram=="-f")
        {
            //QString fileToCompress="C:/aac.txt";
            QString fileToCompress = QString::fromLocal8Bit(argv[2]);
            fileToCompress.replace('\\','/');
            //QString zipFile = "C:/aac.zip";
            QString zipFile = QString::fromLocal8Bit(argv[3]);
            zipFile.replace('\\','/');
            if(!QFile::exists(fileToCompress))
                cout<<"�ļ������ڣ�"<<endl;
            else
            {
                if(QDir::isRelativePath(zipFile))
                {
                    QFileInfo fileinfo(fileToCompress);
                    QString newPath = fileinfo.absolutePath();
                    zipFile=newPath+"/"+zipFile;
                }
                if(!JlCompress::compressFile(zipFile,fileToCompress))
                    cout<<"�����ˣ�������..."<<endl;
                else
                    cout<<"Done,ѹ���ɹ���"<<endl;
            }
        }
        else if(pram=="-d")
        {
            QString dirToCompress = QString::fromLocal8Bit(argv[2]);
            QString zipFile = QString::fromLocal8Bit(argv[3]);
            dirToCompress.replace('\\','/');
            zipFile.replace('\\','/');
            QDir tempdir(dirToCompress);
            if(!tempdir.exists())
                cout<<"Ŀ¼�����ڣ�"<<endl;
            else
            {
                if(QDir::isRelativePath(zipFile))
                {
                    QFileInfo dirinfo(dirToCompress);
                    QDir parentDir=dirinfo.dir();
                    zipFile=parentDir.absolutePath()+"/"+zipFile;
                }
                if(!JlCompress::compressDir(zipFile,dirToCompress,1))
                    cout<<"�����ˣ�������..."<<endl;
                else
                    cout<<"Done,ѹ���ɹ���"<<endl;
            }
        }
        else if(pram=="-u")
        {
            QString zipFile = QString::fromLocal8Bit(argv[2]);
            QString dirToPut = QString::fromLocal8Bit(argv[3]);
            zipFile.replace('\\','/');
            dirToPut.replace('\\','/');
            if(!QFile::exists(zipFile))
                cout<<"ѹ���ļ������ڣ�"<<endl;
            else
            {
                if(QDir::isRelativePath(dirToPut))
                {
                    QFileInfo fileinfo(zipFile);
                    dirToPut=fileinfo.absolutePath()+"/"+dirToPut;
                }
                if(JlCompress::extractDir(zipFile,dirToPut)==QStringList())
                    cout<<"�����ˣ�������..."<<endl;
                else
                    cout<<"Done,��ѹ�ɹ���"<<endl;
            }

        }
        else if(pram=="-ul")
        {
            QString zipFile = QString::fromLocal8Bit(argv[2]);
            zipFile.replace('\\','/');
            QFileInfo zipinfo(zipFile);
            QString currentDir = zipinfo.absolutePath();
            if(!QFile::exists(zipFile))
                cout<<"ѹ���ļ������ڣ�"<<endl;
            else
            {
                if(JlCompress::extractDir(zipFile,currentDir)==QStringList())
                    cout<<"�����ˣ�������..."<<endl;
                else
                    cout<<"Done,��ѹ�ɹ���"<<endl;
            }
        }
    }

    return 1;
    //return a.exec();
}
