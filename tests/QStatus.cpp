// A try to port libgit2 status.c example to libqgit2

#include <QCoreApplication>
#include <QTimer>
#include <iostream>

#include <bitset>

#include "qgitrepository.h"
#include "qgitstatuslist.h"
#include "qgitstatusentry.h"
#include "qgitstatus.h"
#include "qgitstatusoptions.h"

#include "QStatus.h"

using namespace LibQGit2;

QStatus::QStatus()
{
    // Create a new repository object
    Repository * repo = new LibQGit2::Repository();
    
    // Open a local fixed path
    repo->open(QString("/home/leo/projects/libqgit2"));
    
    StatusOptions *opt = new StatusOptions;
    opt->setShowFlags(StatusOptions::ShowIndexAndWorkdir);
    opt->setStatusFlags(StatusOptions::IncludeUnmodified | StatusOptions::IncludeUntracked |
        StatusOptions::RenamesHeadToIndex | StatusOptions::RenamesIdexToWorkdir
    );
            
    // Get the list of status entries
    StatusList status_list = repo->status(opt);
    
    // Count entries
    size_t entries = status_list.entryCount();

    for (size_t i = 0; i < entries; ++i) {
        const StatusEntry entry = status_list.entryByIndex(i);
        
        if (entry.status().isCurrent()) {
            std::cout << "C";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isNewInIndex()) {
            std::cout << "N";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isModifiedInIndex()) {
            std::cout << "M";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isDeletedInIndex()) {
            std::cout << "D";
        } else {
            std::cout << " ";
        }

        if (entry.status().isRenamedInIndex()) {
            std::cout << "R";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isTypeChangedInIndex()) {
            std::cout << "T";
        } else {
            std::cout << " ";
        }
        
        std::cout << " ";
        
        if (entry.status().isNewInWorkdir()) {
            std::cout << "N";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isModifiedInWorkdir()) {
            std::cout << "M";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isDeletedInWorkdir()) {
            std::cout << "D";
        } else {
            std::cout << " ";
        }

        if (entry.status().isRenamedInWorkdir()) {
            std::cout << "R";
        } else {
            std::cout << " ";
        }
        
        if (entry.status().isTypeChangedInWorkdir()) {
            std::cout << "T";
        } else {
            std::cout << " ";
        }
        
        std::cout << " ";
        
        std::cout << entry.path().toStdString() << std::endl;

//        std::bitset<16> x(entry.status().data());
    }
    
}

QStatus::~QStatus()
{}

#include "QStatus.moc"

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QStatus foo;
    return app.exec();
}


