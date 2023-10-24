from exceptions import IncorrectEmailOrPassword
from hashservice import HashService


class SignIn:
    def __init__(self, user_repo):
        self.__user_repo = user_repo  # private attribute

    def perform(self, user_email, user_password):
        user_found = self.__user_repo.find_by_email(user_email)

        if user_found is None:
            raise IncorrectEmailOrPassword

        hash_service = HashService()
        check_password = hash_service.check_password(user_found.password, user_password)

        if check_password:
            return user_found
        else:
            raise IncorrectEmailOrPassword
