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
          <<"                                              由卢鑫畅制作,大作业--MyZIP"<<endl<<endl
          <<"用法："<<"MyZip [-f FileToCompress ZIPFile] [-d DirToCompress ZIPFile] "<<endl
          <<"           "<<"[-h] [-u ZIPFile DirToPut] [-ul ZIPFile]"<<endl<<endl
          <<"选项："<<endl
          <<"-f      "<<"压缩文件，第二个参数是要压缩的文件的绝对路径，第三个参数是\n"
          <<"        "<<"生成的压缩文件所要放置的路径与文件名字，可以是绝对或相对路径\n\n"
          <<"-d      "<<"压缩目录，第二个参数是要压缩的目录的绝对路径，第三个参数是\n"
          <<"        "<<"生成的压缩文件所要放置的路径与文件名字，可以是绝对或相对路径\n\n"
          <<"-u      "<<"解压zip文件，第二参数是zip文件的绝对路径与文件名，第三个参数是\n"
          <<"        "<<"解压后要放置的目录，可以是绝对或相对路径\n\n"
          <<"-ul     "<<"解压zip文件到其所在的文件夹，第二参数是zip文件的绝对路径与文件名\n\n"
          <<"-h      "<<"查看帮助\n"<<endl;
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
                cout<<"文件不存在！"<<endl;
            else
            {
                if(QDir::isRelativePath(zipFile))
                {
                    QFileInfo fileinfo(fileToCompress);
                    QString newPath = fileinfo.absolutePath();
                    zipFile=newPath+"/"+zipFile;
                }
                if(!JlCompress::compressFile(zipFile,fileToCompress))
                    cout<<"出错了，请重试..."<<endl;
                else
                    cout<<"Done,压缩成功！"<<endl;
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
                cout<<"目录不存在！"<<endl;
            else
            {
                if(QDir::isRelativePath(zipFile))
                {
                    QFileInfo dirinfo(dirToCompress);
                    QDir parentDir=dirinfo.dir();
                    zipFile=parentDir.absolutePath()+"/"+zipFile;
                }
                if(!JlCompress::compressDir(zipFile,dirToCompress,1))
                    cout<<"出错了，请重试..."<<endl;
                else
                    cout<<"Done,压缩成功！"<<endl;
            }
        }
        else if(pram=="-u")
        {
            QString zipFile = QString::fromLocal8Bit(argv[2]);
            QString dirToPut = QString::fromLocal8Bit(argv[3]);
            zipFile.replace('\\','/');
            dirToPut.replace('\\','/');
            if(!QFile::exists(zipFile))
                cout<<"压缩文件不存在！"<<endl;
            else
            {
                if(QDir::isRelativePath(dirToPut))
                {
                    QFileInfo fileinfo(zipFile);
                    dirToPut=fileinfo.absolutePath()+"/"+dirToPut;
                }
                if(JlCompress::extractDir(zipFile,dirToPut)==QStringList())
                    cout<<"出错了，请重试..."<<endl;
                else
                    cout<<"Done,解压成功！"<<endl;
            }

        }
        else if(pram=="-ul")
        {
            QString zipFile = QString::fromLocal8Bit(argv[2]);
            zipFile.replace('\\','/');
            QFileInfo zipinfo(zipFile);
            QString currentDir = zipinfo.absolutePath();
            if(!QFile::exists(zipFile))
                cout<<"压缩文件不存在！"<<endl;
            else
            {
                if(JlCompress::extractDir(zipFile,currentDir)==QStringList())
                    cout<<"出错了，请重试..."<<endl;
                else
                    cout<<"Done,解压成功！"<<endl;
            }
        }
    }

    return 1;
    //return a.exec();
}
