/**
 * Bank implementation.
 *
 * @author Martynov Pavel
 */
import java.lang.Integer.max
import java.lang.Integer.min
import java.util.concurrent.locks.ReentrantLock
import kotlin.concurrent.withLock

class BankImpl(n: Int) : Bank {
    private val accounts: Array<Account> = Array(n) { Account() }

    override val numberOfAccounts: Int
        get() = accounts.size

    override fun getAmount(index: Int): Long {
        accounts[index].lock.withLock {
            return accounts[index].amount
        }
    }

    override val totalAmount: Long
        get() {
            var res: Long = 0
            for (i in accounts.indices) {
                accounts[i].lock.lock()
                res += accounts[i].amount
            }
            for (i in accounts.indices.reversed()) {
                accounts[i].lock.unlock()
            }
            return res
        }


    override fun deposit(index: Int, amount: Long): Long {
        require(amount > 0) { "Invalid amount: $amount" }

        val account = accounts[index]
        account.lock.withLock {
            check(!(amount > Bank.MAX_AMOUNT || account.amount + amount > Bank.MAX_AMOUNT)) { "Overflow" }
            account.amount += amount
            return account.amount
        }
    }

    override fun withdraw(index: Int, amount: Long): Long {
        require(amount > 0) { "Invalid amount: $amount" }

        val account = accounts[index]
        account.lock.withLock {
            check(account.amount - amount >= 0) { "Underflow" }
            account.amount -= amount
            return account.amount
        }
    }

    override fun transfer(fromIndex: Int, toIndex: Int, amount: Long) {
        require(amount > 0) { "Invalid amount: $amount" }
        require(fromIndex != toIndex) { "fromIndex == toIndex" }
        val from = accounts[fromIndex]
        val to = accounts[toIndex]

        accounts[min(fromIndex, toIndex)].lock.withLock {
            accounts[max(fromIndex, toIndex)].lock.withLock {
                check(amount <= from.amount) { "Underflow" }
                check(!(amount > Bank.MAX_AMOUNT || to.amount + amount > Bank.MAX_AMOUNT)) { "Overflow" }
                from.amount -= amount
                to.amount += amount
            }
        }
    }

    /**
     * Private account data structure.
     */
    class Account {
        /**
         * Amount of funds in this account.
         */
        var amount: Long = 0
        var lock: ReentrantLock = ReentrantLock()
    }
}