/******************************************************************************

  This source file is part of the MoleQueue project.

  Copyright 2011 Kitware, Inc.

  This source code is released under the New BSD License, (the "License").

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

******************************************************************************/

#include "addqueuedialog.h"
#include "ui_addqueuedialog.h"

#include "queue.h"
#include "queuemanager.h"

namespace MoleQueue {

AddQueueDialog::AddQueueDialog(QueueManager *queueManager, QWidget *parent)
  : QDialog(parent),
    ui(new Ui::AddQueueDialog),
    m_queueManager(queueManager)
{
    ui->setupUi(this);

    ui->typeComboBox->addItems(queueManager->queueTypes());

    connect(this, SIGNAL(accepted()), SLOT(addQueue()));
}

AddQueueDialog::~AddQueueDialog()
{
    delete ui;
}

void AddQueueDialog::addQueue()
{
  Queue *queue = m_queueManager->createQueue(ui->typeComboBox->currentText());

  if(queue){
    queue->setName(ui->nameLineEdit->text());
    m_queueManager->addQueue(queue);
  }
}

} // end MoleQueue namespace