#include "dataimportfromfileform.h"
#include "ui_dataimportfromfileform.h"

DataImportFromFileForm::DataImportFromFileForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataImportFromFileForm)
{
    parentMdi = (MainWindow*) this->parentWidget();
    ui->setupUi(this);
}

DataImportFromFileForm::~DataImportFromFileForm()
{
    parentMdi->setNumberOfSubWindows(parentMdi->getNumberOfSubWindows() - 1);
    delete ui;
}

// false jak nie udalo sie otworzyc pliku, true gdy udalo sie
bool ReadInputCuboidsFromFile(string fileName, CuboidSerie& cuboidSerie)
{
  ifstream fileStream;
  fileStream.open(fileName, ios_base::in);
  string inputLine;
  Cuboid *inputCuboidPointer;
  unsigned short length, width, height, gapPosition = 0;
  unsigned int summaryVolume = 0;

  if (fileStream.fail()){
      cout << "nie udalo sie otworzyc pliku" << endl;
      return false;
  }
  else
  {
    cout << "udalo sie otworzyc plik" << endl;
    getline(fileStream, inputLine);

    gapPosition = inputLine.find(" ");
    cuboidSerie.setSphereLength(stoi(inputLine.substr(0, gapPosition)));
    inputLine.erase(0, gapPosition + 1);

    gapPosition = inputLine.find("\n");
    cuboidSerie.setSphereWidth(stoi(inputLine.substr(0, gapPosition)));
    inputLine.erase(0, gapPosition + 1);

    while(!fileStream.eof())
    {
      inputLine.clear();
      getline(fileStream, inputLine);

      gapPosition = inputLine.find(" ");
      length = stoi(inputLine.substr(0, gapPosition));
      inputLine.erase(0, gapPosition + 1);

      gapPosition = inputLine.find(" ");
      width = stoi(inputLine.substr(0, gapPosition));
      inputLine.erase(0, gapPosition + 1);

      gapPosition = inputLine.find("\n");
      height = stoi(inputLine.substr(0, gapPosition));
      inputLine.erase(0, gapPosition + 1);

      inputCuboidPointer = new Cuboid(length, width, height);
      cuboidSerie.cuboidListForAlgorithm1->push_front(*inputCuboidPointer);

      summaryVolume += length * width * height;
    }

    fileStream.close();

    cuboidSerie.cuboidListForAlgorithm2->assign(cuboidSerie.cuboidListForAlgorithm1->begin(),
                                                 cuboidSerie.cuboidListForAlgorithm1->end());

    cuboidSerie.setInitialSphereHeight(ceil((float)summaryVolume /
        ((float)cuboidSerie.getSphereLength() * (float)cuboidSerie.getSphereWidth())));
    cuboidSerie.setInitialSphereVolume(cuboidSerie.getSphereLength() * cuboidSerie.getSphereWidth()
        * cuboidSerie.getInitialSphereHeight());
  }
  return true;
}

void DataImportFromFileForm::on_buttonBox_accepted()
{
    string fileName;
    vector<CuboidSerie> *cuboidSeries = parentMdi->getCuboidManager().getCuboidSeries();
    CuboidSerie *cuboidSerie = new CuboidSerie();

    if(ui->lineEdit->text().isEmpty())
        return ;

    fileName = ui->lineEdit->text().toStdString();

    if(!ReadInputCuboidsFromFile(fileName, *cuboidSerie))
        return ;

    cuboidSeries->push_back(*cuboidSerie);

    this->~DataImportFromFileForm();
    this->parentMdi->removeSubWindow();
}

void DataImportFromFileForm::on_buttonBox_rejected()
{
    this->~DataImportFromFileForm();
    this->parentMdi->removeSubWindow();
}
