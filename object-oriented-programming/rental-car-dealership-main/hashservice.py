"""
It’s a process of converting one string to another using a hash function.
There are various types of hash functions but there are some basic similarities
that are satisfied by all of them is that hashing is an irreversible process.
i.e. conversion should be only one way, the length of hash should be
fixed, and an input string should uniquely correspond with a hash so that we can compare them later,
this makes it ideal for passwords and authentication.
"""
import bcrypt


class HashService:
    def __init__(self):
        # gera nosso salt, que é uma string pseudoaleatória adicionada ao fim da senha, antes do hashing
        self.salt = bcrypt.gensalt()

    def hash_password(self, password):
        # convertemos a string para bytecode
        bytecode = password.encode('utf-8')
        # finalmente fazemos o hashing da senha, colocando o salt ao fim da password
        return bcrypt.hashpw(bytecode, self.salt)

    def check_password(self, password_in_repo, password):
        # convertemos a string que desejamos encontrar para bytecode
        bytecode = password.encode('utf-8')
        return bcrypt.checkpw(bytecode, password_in_repo)