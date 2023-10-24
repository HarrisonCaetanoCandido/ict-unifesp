from exceptions import IncorrectEmailOrPassword, IncorrectEmail, AccessDenied
from hashservice import HashService
# a intenção é simular um banco de usuários


class InMemoryUserRepository:
    def __init__(self, admin_username, admin_password):
        """
        Python prescribes a convention of prefixing the name of the variable/method with a single or double underscore
        to emulate the behavior of protected and private access specifiers.
        The double underscore __ prefixed to a variable makes it private. It gives a strong suggestion not to touch it
        from outside the class. Any attempt to do so will result in an AttributeError
        """
        self.__admin_username = admin_username  # private attribute
        hash_service = HashService()
        self.__admin_password = hash_service.hash_password(admin_password)  # private attribute
        self.__users = []  # private attribute

    def add_user(self, user):
        self.__users.append(user)

    # método para excluir conta pelo próprio usuário, precisa de senha
    def delete_account(self, email, password):
        user = self.find_by_email(email)
        if user is None:
            raise IncorrectEmailOrPassword

        hash_service = HashService()
        check_password = hash_service.check_password(user.password, password)

        if check_password:
            for index in range(0, len(self.__users)):
                if self.__users[index].email == user.email:
                    del(self.__users[index])
                    return 'This account has been removed'
        else:
            raise IncorrectEmailOrPassword

    """
    método usado por administradores do banco de usuários, não precisa de senha
    -----------------------------------------------------------------------------------------------------------
    como usamos hash nas senhas, é necessário um método interno para um administrador do banco de usuários
    que possa excluir contas sem precisar crackear a senha, caso esse que seria muito custoso e provavelmente não
    funcionaria para senhas muito fortes
    """
    def remove_user(self, email, admin_username, admin_password):
        if admin_username != self.__admin_username:
            raise AccessDenied

        hash_service = HashService()
        if not hash_service.check_password(self.__admin_password, admin_password):
            raise AccessDenied

        user = self.find_by_email(email)
        if user is None:
            raise IncorrectEmail

        for index in range(0, len(self.__users)):
            if self.__users[index].email == user.email:
                del (self.__users[index])
                return 'This account has been removed'

    def find_by_email(self, email):
        for item in self.__users:
            if item.email == email:
                return item

    def get_users_quantity(self):
        return len(self.__users)
