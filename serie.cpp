#include "serie.h"

QHash<QString,Serie *> *Serie::m_series;
QMultiHash<QString,QString> *Serie::m_series_by_country;



Serie::Serie(QObject *parent) :
    QObject(parent)
{
    if(!m_series)
        m_series= new QHash<QString,Serie *>();
    if(!m_series_by_country)
        m_series_by_country = new QMultiHash<QString,QString>();

}

void Serie::setUid(QString value)
{
    m_uid = value;
    m_series->insert(m_uid, this);
    m_series_by_country->insert(m_country_uid,m_uid);
//    qDebug() << m_uid << " " << m_country_uid;
    emit uidChanged();

}

QString Serie::uid()
{
    return m_uid;
}

void Serie::setName(QString value)
{
    m_name = value;
    emit nameChanged();

}

QString Serie::name()
{
    return m_name;
}

void Serie::setCountryUid(QString value)
{
    m_country_uid = value;
    emit countryUidChanged();

}

QString Serie::countryUid()
{
    return m_country_uid;
}

void Serie::setTeamUid(QStringList value)
{
    m_team_list=value;
    emit teamUidChanged();
}

QStringList Serie::teamUid()
{
    return m_team_list;
}

void Serie::setMatchUid(QStringList value)
{
    m_match_list=value;
    emit matchUidChanged();

}

QStringList Serie::matchUid()
{
    return m_match_list;
}

QString Serie::getNameByUid(QString value)
{
    Serie *serie = m_series->value(value);
    if (serie)
        return serie->name();
    else
        return "error";

}

QStringList Serie::getTeamsByUid(QString value)
{
    Serie *serie = m_series->value(value);
    QStringList errorlist;
    errorlist.append("error");
    if (serie)
        return serie->teamUid();
    else
        return errorlist;

}

QStringList Serie::getUidByCountryUid(QString value)
{
    QStringList values = m_series_by_country->values(value);

    return values;

}

void Serie::makeSchedule(QString value)
{
    Serie *serie = m_series->value(value);
    Match *newMatch;
    QStringList teams;
    int countTeams;
    QString uid;
    if (serie){
        teams=serie->m_team_list;
        countTeams=teams.count();
        if(countTeams==6){
//            qDebug()<< "Debug" << teams[0];
            newMatch = new Match();
            newMatch->setHomeTeamUid(teams[5]);
            newMatch->setAwayTeamUid(teams[3]);
            newMatch->setMatchDay(13);
            newMatch->setMatchMonth(9);
            newMatch->setMatchYear(2015);
            uid=serie->name()+teams[5]+teams[3];
            newMatch->setUid(serie->name());
//            qDebug()<< "Debug";
            newMatch = new Match();
            newMatch->setHomeTeamUid(teams[4]);
            newMatch->setAwayTeamUid(teams[2]);
            newMatch->setMatchDay(13);
            newMatch->setMatchMonth(9);
            newMatch->setMatchYear(2015);
            uid=serie->name()+teams[4]+teams[2];
            newMatch->setUid(serie->name());
            newMatch = new Match();
            newMatch->setHomeTeamUid(teams[1]);
            newMatch->setAwayTeamUid(teams[0]);
            newMatch->setMatchDay(13);
            newMatch->setMatchMonth(9);
            newMatch->setMatchYear(2015);
            uid=serie->name()+teams[1]+teams[0];
            newMatch->setUid(serie->name());

        }
    }

}

