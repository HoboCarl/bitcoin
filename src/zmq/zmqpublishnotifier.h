// Copyright (c) 2015-2018 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
#define BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H

#include <zmq/zmqabstractnotifier.h>

class CBlockIndex;

class CZMQAbstractPublishNotifier : public CZMQAbstractNotifier
{
private:
    uint32_t nSequence {0U}; //!< upcounting per message sequence number

public:

    /* send zmq multipart message
       parts:
          * command
          * data
          * message sequence number
    */
    bool SendMessage(const char *command, const void* data, size_t size);

    bool Initialize(void *pcontext) override;
    void Shutdown() override;

    // Common code between txn publishers
    bool NotifyTransactionX(const CTransaction &transaction, const char *pub_type, uint32_t mempool_sequence);
};

class CZMQPublishHashBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex) override;
};

class CZMQPublishHashTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction, uint32_t mempool_sequence) override;
};

class CZMQPublishHashTransactionEvictionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransactionEviction(const CTransaction &transaction, MemPoolRemovalReason reason, uint32_t mempool_sequence) override;
};


class CZMQPublishRawBlockNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyBlock(const CBlockIndex *pindex) override;
};

class CZMQPublishRawTransactionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransaction(const CTransaction &transaction, uint32_t mempool_sequence) override;
};

class CZMQPublishRawTransactionEvictionNotifier : public CZMQAbstractPublishNotifier
{
public:
    bool NotifyTransactionEviction(const CTransaction &transaction, MemPoolRemovalReason reason, uint32_t mempool_sequence) override;
};

#endif // BITCOIN_ZMQ_ZMQPUBLISHNOTIFIER_H
