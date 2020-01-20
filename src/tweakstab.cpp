#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextStream>
#include <QDesktopServices>
#include <dbmanager.h>

///////////////////////TWEAKS TAB///////////////////////

////////////////////////////////SOURCES

//##sources.list.d

void MainWindow::on_openSourcesListDButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening sources.list.d"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/023.openSourcesListD"
           " && "
           "echo Close this window!"
           "; exec bash'");

    //QDesktopServices::openUrl(QUrl("file:///etc/apt/sources.list.d"));

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##sources.list

void MainWindow::on_openSourcesListButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening Sources.list"));

    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    QString status = db.getStatus("textEditor");

    QProcess::startDetached("xterm -e \"sudo -i "+ status +" /etc/apt/sources.list && exit; exec bash\"");
    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_backupSourcesListButton_clicked()
{
    ui->statusBar->showMessage(tr("Backuping sudoers"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/043.backupSourcesList"
           " && "
           "exit"
           "; exec bash'");

    QMessageBox::information(this,tr("Notification"),tr("Backuped OK on \n\n") + QDir::homePath() + "/.ubunsys/backups/sources.list");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_importSourcesListButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                    this,
                    tr("Import your sources.list file here"),
                    QDir::homePath() + "/.ubunsys/backups/sources.list",
                    //getenv("HOME"),
                    //"All files (*.*);;Bak files(*.bak)");
                    "Bak files(*.bak)");

    //QMessageBox::information(this,tr("File Name"),filename);

    // Create a new file

    QFile file (QDir::homePath() + "/.ubunsys/backups/sources.list/restoreSourcesListScript.sh");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "#!/bin/bash\n\nsudo cp " + filename + " /etc/apt/sources.list";

    // optional, as QFile destructor will already do it:
    file.close();

    system("xterm -e '"
           "sudo chmod 777 ~/.ubunsys/backups/sources.list/restoreSourcesListScript.sh"
           "&&"
           "sudo ~/.ubunsys/backups/sources.list/restoreSourcesListScript.sh"
           " && "
           "sudo rm -Rf ~/.ubunsys/backups/sources.list/restoreSourcesListScript.sh"
           " && "
           "exit"
           "; exec bash'");

    //this would normally start the event loop, but is not needed for this
    //minimal example:
    //return app.exec();

    ui->statusBar->showMessage(tr("Done. sources.list restored succesful"));

}

//##OfficialUpdateNotification

void MainWindow::on_checkBoxOfficialUpdateNotification_clicked(bool checked)
{
    if (checked == true){

        qDebug() << checked;

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/054.enableOfficialUpdateNotification"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Enabled"));
    }

    if (checked == false){

        qDebug() << checked;

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/055.disableOfficialUpdateNotification"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Disabled"));
    }

    MainWindow::checkOfficialUpdateNotificationStatus();

}

////////////////////////////////SECURITY

//##sudo without pass all

void MainWindow::on_checkBoxSudoWOPass_clicked(bool checked)
{
    if (checked == true){
        qDebug() << checked;

        ui->statusBar->showMessage(tr("Enabling sudo without pass"));

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/025.enableSudoWithoutPassAll"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

              ui->statusBar->showMessage(tr("Disabling sudo without pass"));

              system("xterm -e '"
                     "~/.ubunsys/downloads/ubuntuScripts-dev/026.disableSudoWithoutPassAll"
                     " && "
                     "exit"
                     "; exec bash'");

              ui->statusBar->showMessage(tr("Done. Now select another action"));
    }

    MainWindow::checkSudoWithoutPassStatus();

}

//##sudo without pass specific

void MainWindow::on_enableSudoWithoutPassSpecificButton_clicked()
{
    ui->statusBar->showMessage(tr("Enabling sudo without pass specific"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/052.enableSudoWithoutPassSpecific"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_disableSudoWithoutPassSpecificButton_clicked()
{
    ui->statusBar->showMessage(tr("Disabling sudo without pass specific"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/053.disableSudoWithoutPassSpecific"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##sudoers.d

void MainWindow::on_openSudoersDButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening sudoers.d"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/051.openSudoersD"
           " && "
           "echo Close this window!"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##hosts

void MainWindow::on_openHostsButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening hosts"));

    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    QString status = db.getStatus("textEditor");

    QProcess::startDetached("xterm -e \"sudo -i "+ status +" /etc/hosts && exit; exec bash\"");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##sudoers

void MainWindow::on_openSudoersFileButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening sudoers"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/027.openSudoersFile"
           " && "
           "echo Close this window!"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_backupSudoersFileButton_clicked()
{
    ui->statusBar->showMessage(tr("Backuping sudoers"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/028.backupSudoersFile"
           " && "
           "exit"
           "; exec bash'");

    QMessageBox::information(this,tr("Notification"),tr("Backuped OK on \n\n") + QDir::homePath() + "/.ubunsys/backups/sudoersFiles");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_importSudoersFileButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                    this,
                    tr("Import your sudoers file here"),
                    QDir::homePath() + "/.ubunsys/backups/sudoersFiles",
                    //getenv("HOME"),
                    //"All files (*.*);;Bak files(*.bak)");
                    "Bak files(*.bak)");

    //QMessageBox::information(this,tr("File Name"),filename);

    ui->statusBar->showMessage(tr("Done. sudoers file restored succesful"));

    // Create a new file

    QFile file (QDir::homePath() + "/.ubunsys/backups/sudoersFiles/restoreSudoersScript.sh");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "#!/bin/bash\n\nsudo cp " + filename + " /etc/sudoers";

    // optional, as QFile destructor will already do it:
    file.close();

    system("xterm -e '"
           "sudo chmod 777 ~/.ubunsys/backups/sudoersFiles/restoreSudoersScript.sh"
           "&&"
           "sudo ~/.ubunsys/backups/sudoersFiles/restoreSudoersScript.sh"
           " && "
           "sudo rm -Rf ~/.ubunsys/backups/sudoersFiles/restoreSudoersScript.sh"
           " && "
           "exit"
           "; exec bash'");

    //this would normally start the event loop, but is not needed for this
    //minimal example:
    //return app.exec();
}

//##firewall

void MainWindow::on_checkBox_firewall_clicked(bool checked)
{
    if (checked != false){
        qDebug() << checked;

        ui->statusBar->showMessage(tr("Enabling firewall"));

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/033.check_ufw_installed"
               " && "
               "~/.ubunsys/downloads/ubuntuScripts-dev/031.enableFirewall"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

              ui->statusBar->showMessage(tr("Disabling firewall"));

              system("xterm -e '"
                     "~/.ubunsys/downloads/ubuntuScripts-dev/033.check_ufw_installed"
                     " && "
                     "~/.ubunsys/downloads/ubuntuScripts-dev/032.disableFirewall"
                     " && "
                     "exit"
                     "; exec bash'");

              ui->statusBar->showMessage(tr("Done. Now select another action"));         

    }

    MainWindow::checkFirewallStatus();
}


////////////////////////////////POWER



////////////////////////////////EXTRAS

void MainWindow::on_goMouseRateCheckerButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://zowie.benq.com/en/support/mouse-rate-checker.html", QUrl::TolerantMode));
    ui->statusBar->showMessage(tr("Go to mouse rate checker. Please wait."));
}

//##Templates

void MainWindow::on_installTemplatesButton_clicked()
{
    ui->statusBar->showMessage(tr("Installing templates"));

    system("bash -c '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/018.installTemplates"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Templates installed succesful. Now select another action"));
}

//##MainBackup

void MainWindow::on_openMainBackupButton_clicked()
{
    ui->statusBar->showMessage(tr("Executing Main Backup"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/045.mainBackup"
           " && "
           "exit"
           "; exec bash'");

    QMessageBox::information(this,tr("Notification"),tr("Backuped OK on \n\n") + QDir::homePath() + "/.ubunsys/backups/lots");


    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Question", "Open folder where located?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {


          system("xterm -e '"
                 "~/.ubunsys/downloads/ubuntuScripts-dev/074.openLots"
                 " && "
                 "echo Close this window!"
                 "; exec bash'");

      }

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_openMainRestoreButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                    this,
                    tr("Import your main backup file here"),
                    QDir::homePath() + "/.ubunsys/backups/lots",
                    //getenv("HOME"),
                    //"All files (*.*);;Bak files(*.bak)");
                    "ZIP files(*.zip)");

    if (!filename.isNull()){
       qDebug() << "No es cero";


    //QMessageBox::information(this,tr("File Name"),filename);

    ui->statusBar->showMessage(tr("Done. Main backup restored succesful"));

    // Create a new file

    QFile file (QDir::homePath() + "/.ubunsys/backups/lots/restoremainBackup.sh");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << "#!/bin/bash\n\nsudo unzip -d ~/.ubunsys/backups/ " + filename;

    // optional, as QFile destructor will already do it:
    file.close();

    system("xterm -e '"
           "sudo chmod 777 ~/.ubunsys/backups/lots/restoremainBackup.sh"
           "&&"
           "sudo ~/.ubunsys/backups/lots/restoremainBackup.sh"
           " && "
           "sudo rm -Rf ~/.ubunsys/backups/lots/restoremainBackup.sh"
           " && "
           "exit"
           "; exec bash'");


//    ui->statusBar->showMessage(tr("Executing Main Restore"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/046.mainRestore"
           " && "
           "exit"
           "; exec bash'");

    QMessageBox::information(this,tr("Notification"),tr("Restored all OK"));

    ui->statusBar->showMessage(tr("Done. Now select another action"));
    }

}

//##rc.local

void MainWindow::on_openRCLocalButton_clicked()
{
    ui->statusBar->showMessage(tr("Opening rc.local"));

    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    QString status = db.getStatus("textEditor");

    QProcess::startDetached("xterm -e \"sudo -i "+ status +" /etc/rc.local && exit; exec bash\"");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##HiddenStartupItems

void MainWindow::on_checkBoxHiddenStartupItems_clicked(bool checked)
{
    if (checked != false){
        qDebug() << checked;

    ui->statusBar->showMessage(tr("Showing"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/038.showHiddenStartupItems"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

    ui->statusBar->showMessage(tr("Unshowing"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/037.unshowHiddenStartupItems"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    MainWindow::checkHiddenStartupItemsStatus();

}

//##dualBoot

void MainWindow::on_runGrubcustomizerButton_clicked()
{
    ui->statusBar->showMessage(tr("Installs/runs grub-customizer. Please wait"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntupackages-master/apps1/grub-customizer"
           " && "
           "sudo grub-customizer"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##Sync Time

void MainWindow::on_runSyncTime_clicked()
{
    ui->statusBar->showMessage(tr("Sync Time"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/changeLinuxtoWindowsTime"
           " && "
           "echo Close this window!"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}


//##edit grub

void MainWindow::on_editGrubButton_clicked()
{
    ui->statusBar->showMessage(tr("Edit grub"));

    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    QString status = db.getStatus("textEditor");

    QProcess::startDetached("xterm -e \"sudo -i "+ status +" /etc/default/grub && exit; exec bash\"");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##update grub

void MainWindow::on_updateGrubButton_clicked()
{
    ui->statusBar->showMessage(tr("Update grub"));

    system("xterm -e '"
           "~/.ubunsys/downloads/ubuntuScripts-dev/081.updateGrub"
           " && "
           "echo Close this window!"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

//##resetDconf

void MainWindow::on_resetDconf_clicked()
{
    ui->statusBar->showMessage(tr("Resetting dconf config"));

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Warning", "Are you completely sure?",
                                    QMessageBox::Yes|QMessageBox::No);
      if (reply == QMessageBox::Yes) {
        qDebug() << "Yes was clicked";
        //QApplication::quit();

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/057.resetDconf"
               " && "
               "echo Close this window!"
               "; exec bash'");


        ui->statusBar->showMessage(tr("Done. Now select another action"));

      } else {
        qDebug() << "Yes was *not* clicked";
        ui->statusBar->showMessage(tr("Execution canceled"));
      }

}

//##asterisks

void MainWindow::on_checkBoxAsterisks_clicked(bool checked)
{
    static const QString path (QDir::homePath() + "/.ubunsys/configurations/config.db");
    DbManager db(path);

    if (db.isOpen())
    {

        if (checked == true){
            qDebug() << checked;

            ui->statusBar->showMessage(tr("Doing visible asterisks"));

            system("xterm -e '"
                   "~/.ubunsys/downloads/ubuntuScripts-dev/021.doVisibleAsterisks"
                   " && "
                   "exit"
                   "; exec bash'");

            ui->statusBar->showMessage(tr("Done. Now select another action"));

        }

        else if (checked == false){
            qDebug() << checked;

            ui->statusBar->showMessage(tr("Doing invisible asterisks"));

            system("xterm -e '"
                   "~/.ubunsys/downloads/ubuntuScripts-dev/022.doInvisibleAsterisks"
                   " && "
                   "exit"
                   "; exec bash'");

            ui->statusBar->showMessage(tr("Done. Now select another action"));

        }
    }

    MainWindow::checkAsterisksStatus();

}

//##hibernation

void MainWindow::on_checkBoxHibernation_clicked(bool checked)
{
    if (checked == true){
        qDebug() << checked;

        ui->statusBar->showMessage(tr("Hibernation enabled"));

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/007.enableHibernation"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

          ui->statusBar->showMessage(tr("Hibernation disabled"));

          system("xterm -e '"
                 "~/.ubunsys/downloads/ubuntuScripts-dev/024.disableHibernation"
                 " && "
                 "exit"
                 "; exec bash'");

          ui->statusBar->showMessage(tr("Done. Now select another action"));
    }

     MainWindow::checkHibernationStatus();
}

//##lock screen

void MainWindow::on_checkBoxLockScreen_clicked(bool checked)
{
    if (checked == true){
        qDebug() << checked;

        ui->statusBar->showMessage(tr("Lock screen Enabled"));

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/036.enableLockScreen"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

          ui->statusBar->showMessage(tr("Lock screen Disabled"));

          system("xterm -e '"
                 "~/.ubunsys/downloads/ubuntuScripts-dev/035.disableLockScreen"
                 " && "
                 "exit"
                 "; exec bash'");

          ui->statusBar->showMessage(tr("Done. Now select another action"));
    }

    MainWindow::checkLockScreenStatus();
}

//##login sound

void MainWindow::on_checkBoxLoginSound_clicked(bool checked)
{
    if (checked == true){
        qDebug() << checked;

        ui->statusBar->showMessage(tr("Login Sound Enabled"));

        system("xterm -e '"
               "~/.ubunsys/downloads/ubuntuScripts-dev/039.enableLoginSound"
               " && "
               "exit"
               "; exec bash'");

        ui->statusBar->showMessage(tr("Done. Now select another action"));

    }

    else if (checked == false){
        qDebug() << checked;

          ui->statusBar->showMessage(tr("Login Sound Disabled"));

          system("xterm -e '"
                       "~/.ubunsys/downloads/ubuntuScripts-dev/040.disableLoginSound"
                 " && "
                 "exit"
                 "; exec bash'");

          ui->statusBar->showMessage(tr("Done. Now select another action"));
    }

    MainWindow::checkLoginSoundStatus();
}

//##fonts

void MainWindow::on_installInfinalityFontsButton_clicked()
{
    ui->statusBar->showMessage(tr("Login Sound Disabled"));

    system("xterm -e '"
                 "~/.ubunsys/downloads/ubuntupackages-master-apps/infinality-fonts"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}

void MainWindow::on_uninstallInfinalityFontsButton_clicked()
{
    ui->statusBar->showMessage(tr("Login Sound Disabled"));

    system("xterm -e '"
                 "~/.ubunsys/downloads/ubuntuScripts-dev/082.uninstallInfinalityFonts"
           " && "
           "exit"
           "; exec bash'");

    ui->statusBar->showMessage(tr("Done. Now select another action"));
}
