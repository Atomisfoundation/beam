// Copyright 2018 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#pragma once

#include <QObject>
#include <QQmlListProperty>
#include <QQueue>
#include <QString>
#include "wallet/transactions/swaps/bridges/bitcoin/client.h"
#include "model/wallet_model.h"
#include "model/settings.h"
#include "viewmodel/messages_view.h"
#include "viewmodel/notifications/exchange_rates_manager.h"
#include "tx_object_list.h"

class WalletViewModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString beamAvailable                 READ beamAvailable              NOTIFY beamAvailableChanged)
    Q_PROPERTY(QString beamReceiving                 READ beamReceiving              NOTIFY beamReceivingChanged)
    Q_PROPERTY(QString beamSending                   READ beamSending                NOTIFY beamSendingChanged)
    Q_PROPERTY(QString beamLocked                    READ beamLocked                 NOTIFY beamLockedChanged)
    Q_PROPERTY(QString beamLockedMaturing            READ beamLockedMaturing         NOTIFY beamLockedChanged)
    Q_PROPERTY(QString beamReceivingChange           READ beamReceivingChange        NOTIFY beamReceivingChanged)
    Q_PROPERTY(QString beamReceivingIncoming         READ beamReceivingIncoming      NOTIFY beamReceivingChanged)
    Q_PROPERTY(QString beamAvailable2ndCurrency           READ beamAvailable2ndCurrency          NOTIFY beamAvailableChanged)
    Q_PROPERTY(QString beamReceiving2ndCurrency           READ beamReceiving2ndCurrency          NOTIFY beamReceivingChanged)
    Q_PROPERTY(QString beamSending2ndCurrency             READ beamSending2ndCurrency            NOTIFY beamSendingChanged)
    Q_PROPERTY(QString beamLocked2ndCurrency              READ beamLocked2ndCurrency             NOTIFY beamLockedChanged)
    Q_PROPERTY(QString beamLockedMaturing2ndCurrency      READ beamLockedMaturing2ndCurrency     NOTIFY beamLockedChanged)
    Q_PROPERTY(QString beamReceivingChange2ndCurrency     READ beamReceivingChange2ndCurrency    NOTIFY beamReceivingChanged)
    Q_PROPERTY(QString beamReceivingIncoming2ndCurrency   READ beamReceivingIncoming2ndCurrency  NOTIFY beamReceivingChanged)
    Q_PROPERTY(bool isAllowedBeamMWLinks             READ isAllowedBeamMWLinks       WRITE allowBeamMWLinks      NOTIFY beamMWLinksAllowed)
    Q_PROPERTY(QAbstractItemModel* transactions      READ getTransactions            NOTIFY transactionsChanged)

public:
    WalletViewModel();

    QString beamAvailable() const;
    QString beamReceiving() const;
    QString beamSending() const;
    QString beamLocked() const;
    QString beamLockedMaturing() const;
    QString beamReceivingChange() const;
    QString beamReceivingIncoming() const;

    QString beamAvailable2ndCurrency() const;
    QString beamReceiving2ndCurrency() const;
    QString beamSending2ndCurrency() const;
    QString beamLocked2ndCurrency() const;
    QString beamLockedMaturing2ndCurrency() const;
    QString beamReceivingChange2ndCurrency() const;
    QString beamReceivingIncoming2ndCurrency() const;

    QAbstractItemModel* getTransactions();
    bool getIsOfflineStatus() const;
    bool getIsFailedStatus() const;
    QString getWalletStatusErrorMsg() const;
    void allowBeamMWLinks(bool value);

    Q_INVOKABLE void cancelTx(const QVariant& variantTxID);
    Q_INVOKABLE void deleteTx(const QVariant& variantTxID);
    Q_INVOKABLE PaymentInfoItem* getPaymentInfo(const QVariant& variantTxID);
    Q_INVOKABLE bool isAllowedBeamMWLinks() const;
    Q_INVOKABLE void exportTxHistoryToCsv();

public slots:
    void onTransactionsChanged(beam::wallet::ChangeAction action, const std::vector<beam::wallet::TxDescription>& items);
    void onTxHistoryExportedToCsv(const QString& data);

signals:
    void beamAvailableChanged();
    void beamReceivingChanged();
    void beamSendingChanged();
    void beamLockedChanged();

    void transactionsChanged();
    void beamMWLinksAllowed();

private:
    WalletModel& _model;
    WalletSettings& _settings;
    ExchangeRatesManager _exchangeRatesManager;
    TxObjectList _transactionsList;
    QQueue<QString> _txHistoryToCsvPaths;
};
