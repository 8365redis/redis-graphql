import graphene
import datetime

# Define the Person type
class Person(graphene.ObjectType):
    name = graphene.String()
    age = graphene.Int()
    city = graphene.String()
    register_time = graphene.Int()
    tags = graphene.List(graphene.String)

# Define the Query type
class Query(graphene.ObjectType):
    persons = graphene.List(Person)

    def resolve_persons(root, info):
        # Sample data
        return [
            Person(name="Alice", age=30, city="New York", register_time=int(datetime.datetime(2020, 1, 1).timestamp()), tags=["student", "gamer"]),
            Person(name="Bob", age=25, city="San Francisco", register_time=int(datetime.datetime(2019, 6, 15).timestamp()), tags=["developer", "musician"]),
            Person(name="Charlie", age=35, city="Chicago", register_time=int(datetime.datetime(2021, 3, 20).timestamp()), tags=["teacher", "runner"])
        ]


def test_basic_graphql():
    # Create the schema
    schema = graphene.Schema(query=Query)

    # Example query
    query_string = '''
    {
    persons {
        name
        age
        city
        registerTime
        tags
    }
    }
    '''

    # Execute the query
    result = schema.execute(query_string)
    print(result.data)
