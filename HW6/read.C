
#include "MovingObject.h"
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <iostream>

void read()
{
    TFile *file = TFile::Open("tree_file.root", "READ");//open file

    if (!file || file->IsZombie()) {
        return;
    }

    TTree *tree = (TTree*)file->Get("tree");//get tree

    if (!tree) {
        return;
    }

    tree->Print();

    MovingObject *object = nullptr;
    tree->SetBranchAddress("object", &object);

    Long64_t nEntries = tree->GetEntries();
    std::cout << "Number of entries: " << nEntries << std::endl;

    // Plot 1: vy vs vx
    TH2D *hist = new TH2D("hist",
        "Velocity components;vx [m/s];vy [m/s]",
        100, -1.5, 1.5,100, -1.5, 1.5);

    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);
        hist->Fill(object->Vx(), object->Vy());
    }

    TCanvas *c1 = new TCanvas("c1", "Velocity components", 800, 600);
    hist->Draw("COLZ");
    c1->SaveAs("velocity_components.pdf");

    // Plot 2
    TCanvas *c2 = new TCanvas("c2", "Selected velocities", 800, 600);

    tree->Draw(
        "sqrt(object.fVx*object.fVx+object.fVy*object.fVy):object.fVz",
        "sqrt(object.fVx*object.fVx+object.fVy*object.fVy+object.fVz*object.fVz)>0.50",
        "P"
    );

    c2->SaveAs("selected_velocities.pdf");

    file->Close();
}
