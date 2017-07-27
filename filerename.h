#ifndef FILERENAME_H
#define FILERENAME_H

#include <QWidget>

#include <QDir>
#include <QFileInfoList>

namespace Ui {
class FileRename;
}

class FileRename : public QWidget
{
    Q_OBJECT

public:
    explicit FileRename(QWidget *parent = 0);
    ~FileRename();

private slots:
    void on_btn_old_clicked();

    void on_btn_rename_clicked();

    void on_lineEdit_new_textChanged(const QString &arg1);

private:
    Ui::FileRename *ui;

    QDir m_dir;
    QFileInfoList m_infoList;
};

#endif // FILERENAME_H
