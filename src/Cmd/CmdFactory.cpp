#include "CmdAbstractBase.h"
#include "CmdFactory.h"
#include <QDomNode>

CmdFactory::CmdFactory ()
{
}

CmdAbstractBase *CmdFactory::createCmd (const QDomNode &nodeCmd)
{
}
